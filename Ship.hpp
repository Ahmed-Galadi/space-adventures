// Constructors
Ship() = default;

Ship(std::string name,
     Stat health,
     Stat power,
     Stat defense,
     Stat luck,
     Level level = 1)
    : name_(std::move(name)),
      health_(health),
      maxHealth_(health),
      power_(power),
      defense_(defense),
      luck_(luck),
      level_(level)
{
    validate();
    clamp();
}

static Ship withMaxHealth(std::string name,
                          Stat maxHealth,
                          Stat power,
                          Stat defense,
                          Stat luck,
                          Level level = 1)
{
    Ship s;
    s.name_ = std::move(name);
    s.maxHealth_ = maxHealth;
    s.health_ = maxHealth;
    s.power_ = power;
    s.defense_ = defense;
    s.luck_ = luck;
    s.level_ = level;
    s.validate();
    s.clamp();
    return s;
}

// Rule of 5 defaulted
Ship(const Ship&) = default;
Ship(Ship&&) noexcept = default;
Ship& operator=(const Ship&) = default;
Ship& operator=(Ship&&) noexcept = default;
~Ship() = default;

// Accessors
std::string_view name() const noexcept { return name_; }
Stat health() const noexcept { return health_; }
Stat maxHealth() const noexcept { return maxHealth_; }
Stat power() const noexcept { return power_; }
Stat defense() const noexcept { return defense_; }
Stat luck() const noexcept { return luck_; }
Level level() const noexcept { return level_; }

bool alive() const noexcept { return health_ > 0; }
float healthRatio() const noexcept {
    return maxHealth_ ? static_cast<float>(health_) / static_cast<float>(maxHealth_) : 0.0f;
}

// Mutators with validation and clamping
Ship& setName(std::string n) {
    if (n.empty()) throw std::invalid_argument("Ship name cannot be empty");
    name_ = std::move(n);
    return *this;
}

Ship& setPower(Stat p) noexcept { power_ = p; return *this; }
Ship& setDefense(Stat d) noexcept { defense_ = d; return *this; }
Ship& setLuck(Stat l) noexcept { luck_ = l; return *this; }

Ship& setLevel(Level lvl) {
    if (lvl < 1) throw std::invalid_argument("Level must be >= 1");
    level_ = lvl;
    return *this;
}

Ship& setMaxHealth(Stat mh) {
    if (mh == 0) throw std::invalid_argument("Max health must be > 0");
    maxHealth_ = mh;
    if (health_ > maxHealth_) health_ = maxHealth_;
    return *this;
}

Ship& setHealth(Stat h) {
    if (maxHealth_ == 0) throw std::logic_error("Max health must be set before health");
    health_ = std::min(h, maxHealth_);
    return *this;
}

// Combat-like operations
// Returns the actual damage dealt after defense. Does not go below 0.
Stat dealDamageTo(Ship& target) const {
    if (!alive()) return 0;
    const Stat raw = power_;
    const Stat mitigated = (raw > target.defense_) ? (raw - target.defense_) : 0;
    const Stat critBonus = critRoll() ? raw / 2 : 0; // mild crit: +50% of base
    const Stat dmg = saturatingAdd(mitigated, critBonus);
    target.applyDamage(dmg);
    return dmg;
}

// Heals this ship by amount; returns actual healed amount.
Stat heal(Stat amount) {
    const Stat before = health_;
    health_ = std::min<Stat>(saturatingAdd(health_, amount), maxHealth_);
    return health_ - before;
}

// Leveling: scales some stats; returns new level
Level levelUp(Level delta = 1) {
    if (delta < 1) return level_;
    // Simple scalable growth; tune to your game
    for (Level i = 0; i < delta; ++i) {
        level_ = safeAdd(level_, 1);
        power_ = safeAdd(power_, 2);
        defense_ = safeAdd(defense_, 2);
        maxHealth_ = safeAdd(maxHealth_, 10);
        // modest luck growth
        luck_ = std::min<Stat>(safeAdd(luck_, 1), 100);
    }
    // Restore some health on level up
    heal(10 * static_cast<Stat>(delta));
    clamp();
    return level_;
}

// Ordering and equality (by name then level then stats)
auto operator<=>(const Ship&) const = default;

// Serialization-friendly print
friend std::ostream& operator<<(std::ostream& os, const Ship& s) {
    os << "Ship{name=\"" << s.name_
       << "\", lvl=" << s.level_
       << ", hp=" << s.health_ << "/" << s.maxHealth_
       << ", pow=" << s.power_
       << ", def=" << s.defense_
       << ", luck=" << s.luck_
       << "}";
    return os;
}void validate() const {
    if (name_.empty()) throw std::invalid_argument("Ship name cannot be empty");
    if (maxHealth_ == 0) throw std::invalid_argument("Max health must be > 0");
    if (level_ < 1) throw std::invalid_argument("Level must be >= 1");
    if (luck_ > 100) throw std::invalid_argument("Luck should be in [0, 100]");
}

void clamp() {
    if (health_ > maxHealth_) health_ = maxHealth_;
    if (luck_ > 100) luck_ = 100;
}

void applyDamage(Stat dmg) {
    if (dmg == 0 || health_ == 0) return;
    health_ = (dmg >= health_) ? 0 : static_cast<Stat>(health_ - dmg);
}

bool critRoll() const noexcept {
    if (luck_ == 0) return false;
    // Deterministic placeholder: replace with RNG in implementation unit.
    // For header-only predictability, use simple hash of name and level.
    std::size_t seed = std::hash<std::string>{}(name_) ^ (static_cast<std::size_t>(level_) << 1);
    seed ^= static_cast<std::size_t>(power_) + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
    const std::size_t mod = 101; // map to 0..100
    const std::size_t roll = (seed % mod);
    return roll < luck_;
}

static Stat safeAdd(Stat a, Stat b) noexcept {
    const auto max = std::numeric_limits<Stat>::max();
    if (a > max - b) return max;
    return a + b;
}

static Stat saturatingAdd(Stat a, Stat b) noexcept { return safeAdd(a, b); }
};

namespace std {
template<>
struct hash<Ship> {
size_t operator()(const Ship& s) const noexcept {
// Combine essential identity attributes
size_t h = std::hashstd::string{}(std::string{s.name()});
h ^= static_cast<size_t>(s.level()) + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
h ^= static_cast<size_t>(s.power()) + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
return h;
}
};
}
