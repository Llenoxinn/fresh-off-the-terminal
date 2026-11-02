# MPA 2: Bantugans, Fight!

CMSC 21 machine problem assignment on **structures and enumerations**: simulate turn-based duels between two warriors, each with health, manna, a weapon, a shield, a spell and a counter-spell, and print both warriors' stats after every turn.

## Contents

- [Story](#story)
- [Rules of the Duel](#rules-of-the-duel)
  - [Bantugan stats](#bantugan-stats)
  - [Weapons](#weapons)
  - [Shields](#shields)
  - [Kiss of the Jade Palapa (spell)](#kiss-of-the-jade-palapa-spell)
  - [Bai-a-Labi's Blink (counter-spell)](#bai-a-labis-blink-counter-spell)
  - [Randomness](#randomness)
- [Input](#input)
- [Output](#output)
- [Sample](#sample)
- [Sample Walkthrough](#sample-walkthrough)
- [Rules Not Spelled Out in the Statement](#rules-not-spelled-out-in-the-statement)
- [Modeling with Structures and Enumerations](#modeling-with-structures-and-enumerations)
- [Turn Algorithm](#turn-algorithm)
- [Testing Checklist](#testing-checklist)
- [Honor Code](#honor-code)

---

## Story

> *This is fiction loosely based on one of the largest ethnic groups in Mindanao.*

In **Pat a Pangampong sa Ranao**, seventeen **Panoroganan** (royal houses), the *Sapolo-ago-pito-a-Panoroganan*, have lived in chaos for 100 years:

| | | | |
|---|---|---|---|
| Butig | Pagayawan | Bayang | Dumalondong |
| Macadar Sultan Mardan | Masiu | Datu a Cabugatan | Bansayan |
| Rogan | Taporog | Minitupad | Borocot |
| Bacolod | Maribo | Ramain | Ditsaan |
| Baloi | | | |

All seventeen houses live around the **Great Lake of Ranao**, whose fish could feed its almost 900,000 Iranaons. Out of greed, the houses turned their **awang** (fishing boats) into killing machines that launch gold-plated spears at any other awang within 5 meters. Weaker houses allied with stronger ones, until the seventeen merged into **two great Pangampongs**: one led by the **Royal House of Datu a Cabugatan**, the other by the **Royal House of Baloi**.

The **Papanoka Mra**, the legendary bird that guards the lake and the source of all life around it, spoke to all Iranaons for the first time in 500 years. He wants the seventeen houses united under one true **Bantugan** (warrior) of his choosing.

The two Pangampongs built an arena where Bantugans from their allied houses duel to the death until one champion is left. The two champions will then journey beneath the lake, to the **Bathymetris**, to find the **Golden Kampilan** and the **Scarlet Kutyapi**. The victor will bring Pat-a-Pangampong-sa-Ranao back to its golden age, or spell its doom.

**Your task:** the Papanoka Mra has asked you to oversee the arenas and **simulate the duels**.

---

## Rules of the Duel

### Bantugan stats

| Stat | Start | Max | Notes |
|---|---|---|---|
| Health | 10 | 10 | Reaching 0 means the Bantugan falls |
| Manna | 10 | 10 | Regenerates **+2 per turn** |
| Weapon | given | – | One of three, fixed for the whole duel |
| Shield | given | – | One of three, fixed for the whole duel |
| Jade Palapa | no | – | Found during the duel |
| Bai-a-Labi's Blink | no | – | Found during the duel, single use |

The duel is **turn-based**: a Bantugan may attack only on his own turn, and the two take turns.

### Weapons

| Code | Weapon | Damage |
|---|---|---|
| 1 | Wooden Spear | 1 |
| 2 | Silver Ax | 2 |
| 3 | Diamond Scythe | 3 |

### Shields

A shield only works if the defender raises it **at the right time**. If he doesn't, he takes the weapon's **full** damage.

When the shield **is** raised in time:

| Attacker's weapon ↓ / Defender's shield → | Wooden Shield | Silver Shield | Diamond Shield |
|---|---|---|---|
| Wooden Spear (1) | **0**: neutralized | **1** (see note) | **0**, and the attacker takes **1** |
| Silver Ax (2) | **1**: repels 1 of 2 | **0**: neutralized | **0**, and the attacker takes **2** |
| Diamond Scythe (3) | **3**: no effect | **2**: repels 1 of 3 | **0**: neutralized |

The pattern: a shield **neutralizes its own tier**, only partly blocks **higher** tiers, and the diamond shield **reflects** lower tiers back at the attacker.

> **Note on Silver Shield vs. Wooden Spear:** the statement says "the opponent gets 1 damage point". Read literally alongside the other rules, the defender takes 1. But following the pattern above, where lower-tier weapons get reflected by a higher shield, it could instead mean the **attacker** takes 1. See [Rules Not Spelled Out](#rules-not-spelled-out-in-the-statement).

### Kiss of the Jade Palapa (spell)

- The only spell. A Bantugan can cast it only if he has **found the Jade Palapa** and has **at least 6 manna**.
- Casting it **costs 6 manna** and **replaces** the weapon attack for that turn.
- If the opponent doesn't counter it, it deals **4 damage**.
- The Palapa is used up once cast.

### Bai-a-Labi's Blink (counter-spell)

- A ruby mirror with a golden frame. It is the **only** way to counter the Jade Palapa.
- Using it **costs 6 manna**.
- **Single use**: it disappears after countering a spell.

### Randomness

In the real game, these are random:

| Event | Probability |
|---|---|
| Weapon and shield at the start of the duel | uniform over 3 |
| Stumbling upon Bai-a-Labi's Blink in a turn | 1/20 |
| Raising the shield at the right time | 1/3 |

**For submission, every random value is read from the input** instead, so the output can be auto-checked. You may also make a playable version that generates them.

---

## Input

```
c                       number of test cases
── per test case ──
w1 s1                   Bantugan timan: weapon, shield (1–3 each)
w2 s2                   Bantugan dua:   weapon, shield
f                       who goes first: 1 = timan, 2 = dua
t                       number of turns EACH Bantugan gets (2t turns in total)
── per turn (2t times) ──
p1 b1 p2 b2             found Palapa / Blink this turn (0 or 1)
                          p1 b1: the Bantugan who took the FIRST turn of the duel
                          p2 b2: the other Bantugan
a                       attacker casts the Jade Palapa? (1 = yes, 0 = weapon attack)
d u                     defender raises shield in time? (0/1), uses Blink? (0/1)
```

**Example header**

```
1           one test case
1 1         timan: Wooden Spear, Wooden Shield
3 2         dua:   Diamond Scythe, Silver Shield
1           timan attacks first
```

**Example turn**

```
0 0 0 1     first Bantugan found nothing; the other found Bai-a-Labi's Blink
0           attacker uses his weapon
1 0         defender raises his shield in time, doesn't use the Blink
```

- All four flags on the first line are **never all 1**: there is only one Jade Palapa and one Blink.
- Not every test case ends with a winner. The duel may simply run out of turns.

---

## Output

**After every turn**, print both Bantugans' stats, timan first:

```
BANTUGAN TIMAN
Health: <h> Mana: <m> Weapon: <weapon> Shield: <shield> Jade Palapa: <0/1> Bai-a-Labi's Blink: <0/1>
BANTUGAN DUA
Health: <h> Mana: <m> Weapon: <weapon> Shield: <shield> Jade Palapa: <0/1> Bai-a-Labi's Blink: <0/1>
```

Names used in the stats line:

| Code | Weapon | Shield |
|---|---|---|
| 1 | `Wooden Spear` | `Wooden Shield` |
| 2 | `Silver Ax` | `Silver Shield` |
| 3 | `Diamond Scythe` | `Diamond Shield` |

**When the duel ends:**

| Outcome | Message |
|---|---|
| Bantugan dua (2) wins | `BANTUGAN TIMAN FALLS! MAY THE PAPANOKA MRA REWARD HIS COURAGE GRACIOUSLY. TO THE LAKE RANAO!` |
| Bantugan timan (1) wins | `BANTUGAN DUA FALLS! MAY THE PAPANOKA MRA REWARD HIS COURAGE GRACIOUSLY. TO THE LAKE RANAO!` |
| Both fall | `DRAW! BOTH BANTUGANS SUCCUMBED AND WILL BE OFFERED TO LAKE RANAO AS SACRIFICE. MAY THE PAPANOKA MRA REWARD THEM GRACIOUSLY.` |

---

## Sample

**Input**

```
1
1 1
1 1
1
3
0 0 0 0
0
1 0
0 0 0 0
0
0 0
1 0 0 0
1
0 0
0 0 0 0
0
1 0
0 0 0 0
0
1 0
0 0 0 1
0
1 0
```

**Output**

```
BANTUGAN TIMAN
Health: 10 Mana: 10 Weapon: Wooden Spear Shield: Wooden Shield Jade Palapa: 0 Bai-a-Labi's Blink: 0
BANTUGAN DUA
Health: 10 Mana: 10 Weapon: Wooden Spear Shield: Wooden Shield Jade Palapa: 0 Bai-a-Labi's Blink: 0
BANTUGAN TIMAN
Health: 9 Mana: 10 Weapon: Wooden Spear Shield: Wooden Shield Jade Palapa: 0 Bai-a-Labi's Blink: 0
BANTUGAN DUA
Health: 10 Mana: 10 Weapon: Wooden Spear Shield: Wooden Shield Jade Palapa: 0 Bai-a-Labi's Blink: 0
BANTUGAN TIMAN
Health: 9 Mana: 4 Weapon: Wooden Spear Shield: Wooden Shield Jade Palapa: 0 Bai-a-Labi's Blink: 0
BANTUGAN DUA
Health: 6 Mana: 10 Weapon: Wooden Spear Shield: Wooden Shield Jade Palapa: 0 Bai-a-Labi's Blink: 0
BANTUGAN TIMAN
Health: 9 Mana: 4 Weapon: Wooden Spear Shield: Wooden Shield Jade Palapa: 0 Bai-a-Labi's Blink: 0
BANTUGAN DUA
Health: 6 Mana: 10 Weapon: Wooden Spear Shield: Wooden Shield Jade Palapa: 0 Bai-a-Labi's Blink: 0
BANTUGAN TIMAN
Health: 9 Mana: 6 Weapon: Wooden Spear Shield: Wooden Shield Jade Palapa: 0 Bai-a-Labi's Blink: 0
BANTUGAN DUA
Health: 6 Mana: 10 Weapon: Wooden Spear Shield: Wooden Shield Jade Palapa: 0 Bai-a-Labi's Blink: 0
BANTUGAN TIMAN
Health: 9 Mana: 6 Weapon: Wooden Spear Shield: Wooden Shield Jade Palapa: 0 Bai-a-Labi's Blink: 0
BANTUGAN DUA
Health: 6 Mana: 10 Weapon: Wooden Spear Shield: Wooden Shield Jade Palapa: 0 Bai-a-Labi's Blink: 1
```

---

## Sample Walkthrough

Both Bantugans have a Wooden Spear and a Wooden Shield. Timan goes first, and each gets 3 turns, so there are 6 turns in total.

| Turn | Attacker | Found | Action | Defense | Result | Timan H/M | Dua H/M |
|---|---|---|---|---|---|---|---|
| 1 | Timan | – | Spear | shield in time | Wooden Shield neutralizes the spear | 10 / 10 | 10 / 10 |
| 2 | Dua | – | Spear | no shield | Timan takes 1 | **9** / 10 | 10 / 10 |
| 3 | Timan | Timan: Palapa | **Jade Palapa** | no Blink | Dua takes 4, Timan spends 6 manna | 9 / **4** | **6** / 10 |
| 4 | Dua | – | Spear | shield in time | Neutralized | 9 / 4 | 6 / 10 |
| 5 | Timan | – | Spear | shield in time | Neutralized. Timan regenerates 2 manna | 9 / **6** | 6 / 10 |
| 6 | Dua | Dua: Blink | Spear | shield in time | Neutralized. Dua now holds the Blink | 9 / 6 | 6 / 10 |

Nobody falls within the 3 turns each, so no final message is printed.

What the sample reveals:

- **Manna regenerates for the attacker, at the start of his turn**, capped at 10. Timan's manna stays at 4 during Dua's turn 4, then rises to 6 on Timan's turn 5. On turn 3 he was at 10, so the regeneration was capped and casting left him at 4.
- **An item found on a turn can be used on that same turn.** Timan finds the Palapa on turn 3 and casts it right away. Afterwards the Palapa shows `0` because it is used up.
- **The flag order follows who went first in the duel, not the current attacker.** On turn 6, Dua is attacking, yet `0 0 0 1` gives the Blink to **Dua**. So the last two flags belong to the Bantugan who did **not** take the duel's first turn, here Dua.
- **Stats are printed after the turn is resolved.**

---

## Rules Not Spelled Out in the Statement

Decide these, keep them consistent, and check them against any extra test cases you're given.

| Question | Reasonable choice |
|---|---|
| Silver Shield vs. Wooden Spear: who takes the 1 damage? | The statement says "the opponent". Pick one reading and note it in a comment |
| The attacker chooses the Palapa but doesn't have it, or has under 6 manna | Fall back to a weapon attack |
| The defender chooses the Blink but doesn't have it, or has under 6 manna | The spell goes through |
| Does a shield block the spell? | No. Only the Blink counters it |
| Does the Blink do anything against a weapon attack? | No. It only counters the spell, and it is not used up |
| Can health go below 0? | Clamp it to 0 when printing, or store it at 0 |
| When to check for a fallen Bantugan | After each turn's stats are printed. Then print the message and stop the duel |
| A duel ends early but turns remain in the input | **Still read the remaining turn lines**, or they spill into the next test case |
| Can a Bantugan hold a second Palapa or Blink? | No. There is only one of each |

---

## Modeling with Structures and Enumerations

This MP is the reason structures exist: each Bantugan has **six related fields** that belong together.

**Enumerations** give names to the codes `1`, `2`, `3`:

```c
typedef enum { WOODEN_SPEAR = 1, SILVER_AX, DIAMOND_SCYTHE } Weapon;
typedef enum { WOODEN_SHIELD = 1, SILVER_SHIELD, DIAMOND_SHIELD } Shield;
typedef enum { TIMAN = 1, DUA = 2 } Side;
```

Starting at `1` lets the input codes be stored directly: `b.weapon = (Weapon) w;`.

**A structure** groups one Bantugan's state:

```c
typedef struct {
    int health;
    int mana;
    Weapon weapon;
    Shield shield;
    int hasPalapa;      // 0 or 1
    int hasBlink;       // 0 or 1
} Bantugan;
```

**Two Bantugans** fit in an array, so "attacker" and "defender" are just indexes that swap each turn:

```c
Bantugan b[2];                     // b[0] = timan, b[1] = dua
int atk = first - 1, def = 1 - atk;
// after each turn:
atk = 1 - atk; def = 1 - def;
```

**Lookup tables** replace long `if` chains:

```c
const char *WEAPON_NAME[] = { "", "Wooden Spear", "Silver Ax", "Diamond Scythe" };
const char *SHIELD_NAME[] = { "", "Wooden Shield", "Silver Shield", "Diamond Shield" };

// damage to the DEFENDER when the shield is raised in time: [weapon][shield]
const int BLOCKED_DMG[4][4] = {
    { 0, 0, 0, 0 },
    { 0, 0, 1, 0 },     // Wooden Spear  vs wooden, silver, diamond
    { 0, 1, 0, 0 },     // Silver Ax
    { 0, 3, 2, 0 },     // Diamond Scythe
};

// damage REFLECTED to the ATTACKER (diamond shield vs lower weapons)
const int REFLECT_DMG[4][4] = {
    { 0, 0, 0, 0 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 2 },
    { 0, 0, 0, 0 },
};
```

If you read Silver Shield vs. Wooden Spear as reflected damage, move that `1` from `BLOCKED_DMG[1][2]` to `REFLECT_DMG[1][2]`.

**Functions that take a structure** keep `main` short. Pass a pointer when the function must change it:

```c
void printStats(const char *name, Bantugan b);
void regenerate(Bantugan *b);              // b->mana = min(b->mana + 2, 10)
void attack(Bantugan *atk, Bantugan *def, int castPalapa, int shieldUp, int useBlink);
```

`b.health` accesses a field of a structure. `b->health` does the same through a pointer, and is shorthand for `(*b).health`.

---

## Turn Algorithm

```
for each test case:
    read both weapons and shields; set health = 10, mana = 10, no items
    read who goes first; read t
    over = 0
    repeat 2t times:
        read p1 b1 p2 b2, a, d u          ← always read, even if over
        if over: continue

        give the Palapa/Blink to the first-turn Bantugan (p1, b1) and the other (p2, b2)
        attacker regenerates 2 manna (max 10)

        if a == 1 and attacker has the Palapa and mana >= 6:
            attacker mana -= 6; attacker loses the Palapa
            if u == 1 and defender has the Blink and mana >= 6:
                defender mana -= 6; defender loses the Blink   ← countered
            else:
                defender health -= 4
        else:
            dmg = weapon damage
            if d == 1:
                defender health -= BLOCKED_DMG[weapon][shield]
                attacker health -= REFLECT_DMG[weapon][shield]
            else:
                defender health -= dmg

        print both stats (timan first)
        if both health <= 0: print DRAW, over = 1
        else if timan health <= 0: print TIMAN FALLS, over = 1
        else if dua health <= 0: print DUA FALLS, over = 1

        swap attacker and defender
```

---

## Testing Checklist

| Case | What it checks |
|---|---|
| The sample | Regeneration timing, same-turn Palapa use, flag order |
| Dua goes first (`f = 2`) | Flags `p1 b1` now belong to **dua**; output is still timan first |
| Every weapon × shield, shield raised | All 9 cells of the damage table |
| Shield not raised | Full weapon damage regardless of shield |
| Diamond Shield vs. Spear or Ax | The attacker loses health |
| Palapa with under 6 manna | Falls back to a weapon attack |
| Palapa countered by the Blink | No damage; both spend 6 manna; both items gone |
| Blink owned but not used | The Blink stays (`1`) |
| A Bantugan reaches 0 health | Correct message; remaining input still consumed |
| Two test cases in a row | State is reset between duels |
| Health would drop below 0 | Printed value matches your chosen rule |

---

## Honor Code

Use the appropriate version, written as a comment in the first lines of the solution, before any preprocessor directives:

> I declare, upon my honor, that I did this machine problem assignment by myself using references from the lecture notes and MPs.

> I declare, upon my honor, that I did this machine problem assignment by myself using online resources, except LLMs, from the following (please cite the online sources). Further, my solution is not a copy from the aforementioned sources.
