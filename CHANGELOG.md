# Goalogic Changelog

# Release v0.0.8 — The "Master Architect" Update
## Global Changes:
- **Structural Revolution** — The entire game engine has been completely rewritten using a modular multi-file architecture. All logic for Players, Teams, and Match mechanics is now separated into dedicated modules.

- **Expanded Rosters** — Team capacity has been increased to 16 players per side. All players are now actively involved in the match, creating a massive temporary 16-vs-16 gameplay experience.

## Minor Changes:
- **Enhanced File Parser** — The loading system for players.txt is now much more robust. It automatically cleans up unnecessary spaces and empty lines.

- **Interface Fluidity** — Integrated a screen-refresh system that clears the console between episodes.

- **Atmospheric Pacing** — Added tactical delays and loading effects during key match events.

- **Input Safety** — Improved menu navigation with basic input validation to prevent crashes.
---
# Release v0.0.7 — The "Data & Muscles" Update
## Global Changes:
- **External Database** — The game now loads the entire roster from an external file. You can now manage your team without touching the source code.

- **Physics Attribute** — Added a new Physics stat. This attribute directly modifies injury risks: high physics provides a survival bonus.

- **Manual Player Creation** — Added an interactive "Scouting" mode in the menu for custom player generation.

## Minor Changes:
- **Balance Overhaul** — Refined the injury logic based on a combination of current Stamina and Physics levels.

- **Extended Parser** — Upgraded the file reading engine to support 8 unique attributes for outfield players and 10 for goalkeepers.

- **UI Improvements** — Added new prompts and status messages for the manual creation process.
---
# Release v0.0.6 — The "Pain & Glory" Update
## Global Changes:
- **Injury System** — Added a complex injury engine. Injured players leave the pitch immediately, and their stamina drops to 0.

- **Risk & Fatigue Tie-in** — Injury probability is now tied to exhaustion. Playing with low energy (below 20%) significantly increases the chance of a career-ending accident.

- **Visual Polish** — New ANSI styles for injury reports and key match events.

## Minor Changes:
- **Smart Roster Management** — The match engine now automatically identifies and skips injured players during action sequences.

- **Logic Fixes** — Fixed "zombie-player" bugs by improving stamina threshold checks.
---
# Release v0.0.5 — The "Guardian" Update
## Global Changes:
- **Goalkeepers Implementation** — Introduced unique stats for GKs (Reflexes, Jumping) and a specialized OVR formula.

- **Stamina Rework** — The opponent's performance is now dynamically affected by their stamina levels, mirroring the player's mechanics.

- **Counter-Attack Expansion** — Added new scenarios and outcomes to the counter-attack engine.

## Minor Changes:
- **Input Buffer Fix** — Resolved an issue where menus were skipped automatically due to leftover characters in the console buffer.

- **Memory Management** — Implemented destructors in the Team class to ensure proper cleanup of player pointers.
---
# Release v0.0.4 — The "Tactical Risk" Update
## Global Changes:
- **Counter-Attack Engine** — Implemented a threat system where the opponent can now seize the initiative. It is now possible to lose a match.

- **Opponent AI Squad** — Introduced a permanent rival team with 5 unique players to challenge the user.

- **Pause System Enhancement** — Refined the pacing between match events for better readability.
---
# Release v0.0.3 — The "Intelligence" Update
## Global Changes:
- **Smart OVR System** — Replaced static ratings with a dynamic OVR formula that calculates player value based on their key attributes.

- **Defensive Statistics** — Added specific attributes for defensive actions, allowing for more balanced player roles.

- **Stamina Buff** — Rebalanced the stamina depletion rates to make long-term match management more challenging.
---
# Release v0.0.2 — The "Squad Foundations" Update
## Global Changes:
- **Stamina System Genesis** — Introduced the core exhaustion mechanic where player actions consume energy.

- **Squad Expansion** — Added new players to the database, including the first customized "legendary" units.

- **Team Viewer** — Implemented a dedicated menu to inspect current team stats and attributes.
---
# Release v0.0.1 — The "Kickoff" Update
## Global Changes:
- **Core Concept** — Initial release of the turn-based football simulation engine.

- **Basic Match Logic** — Created the fundamental "Episode" system for simulating match events.

- **Prototype Team** — Implemented basic player structures and name generation.
