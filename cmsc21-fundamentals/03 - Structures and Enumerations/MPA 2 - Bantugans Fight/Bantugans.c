/*

I declare, upon my honor, that I did this machine problem assignment by myself
using references from the lecture notes and MPs.



================================whatever====================================

ISTG KAPILA NANIGIEVALUATE AAAAAHTAWJFHAWUGHNAWGNBSGAHJFJSAHJK
> Shield lamessaaaaa

shields

    wooden = 1,
    silver = 2,
    diamond = 3,

weapontypes
    wooden_spear = 1,
    silver_ax = 2,
    diamond_scythe = 3,

weakest shield - wooden;
weakest wpn - wooden_Spear
sakit gihapon siyah
>  Wooden shield  vs wooden spear   -> 0 dmg to defender(neutralises)
>  Wooden shield  vs silver ax      -> 1 dmg to defender=(repels 1 of 2)
> Wooden shield  vs diamond scythe -> 3 dmg to defender(no repel ull dmg)
>
>      Silver shield  vs wooden spear   -> 1 dmg to ATTACKER(reflects)
>   Silver shield  vs silver ax      -> 0 dmg to defender(neutralises)
>  Silver shield  vs diamond scythe -> 2 dmg to defender(repels 1 of 3)
>
>  Diamond shield vs wooden spear   -> 1 dmg to ATTACKER(reflects full)
>  Diamond shield vs silver ax      -> 2 dmg to ATTACKER(reflects full)
>   Diamond shield vs diamond scythe -> 0 dmg to defender*eeutralises)
>
>  Shield NOT raised -> defender takes full weapon damage (1-3).
============================================================================

*/
#include<stdio.h>

typedef enum {
    wooden_spear = 1,
    silver_ax = 2,
    diamond_scythe = 3,
}weaponType;

typedef enum {
    wooden = 1,
    silver = 2,
    diamond = 3,
}shieldType;

typedef struct {
    int hp;
    int mana;
    weaponType wpn;
    shieldType shld;
    int hBlink;
    int hPalapa;
}Bantugan;

#define HEALTH_BAR_FULL 10
#define MANA_FULL  10
#define REGEN 2
#define PALAPA_CHARGE 6
#define PALAPA_PENDMG 4
#define BLINK_CHARGE 6

void isaKangBantugan(const char *sinetch, Bantugan *b);
void validity(Bantugan *b);
void attack(Bantugan *attacker, Bantugan *defender, int palapa, int sh, int blink);

int main() {
    int c;
    scanf("%i", &c);
    while(c--) {

        Bantugan timan = { HEALTH_BAR_FULL, MANA_FULL, 0, 0, 0, 0};
        Bantugan dua = { HEALTH_BAR_FULL, MANA_FULL, 0, 0, 0, 0};

        int weapon_num, shield_num;
        int who_should_go_first;

        scanf("%i %i", &weapon_num, &shield_num);
        timan.wpn = (weaponType)weapon_num;
        timan.shld = (shieldType)shield_num;

        scanf("%i %i", &weapon_num, &shield_num);
        dua.wpn = (weaponType)weapon_num;
        dua.shld = (shieldType)shield_num;
        scanf("%i", &who_should_go_first);

        int t;
        scanf("%i",&t);
        int gameover=0;
        int dedznasyah=0;
        while(t!=0) {
            int turn_first = who_should_go_first;
            for(int half = 0; half < 2; half++)
            {
                int palapa_first, blink_first, palapa_second, blink_second;
                scanf("%i %i %i %i", &palapa_first, &blink_first, &palapa_second, &blink_second);
                int Palapa_atck;
                scanf("%i", &Palapa_atck);

                int sh_def, bl_def;
                scanf("%i %i", &sh_def, &bl_def);

                if(dedznasyah) continue;
                if(turn_first == 1) {
                    timan.hPalapa = palapa_first;
                    timan.hBlink  = blink_first;
                    dua.hPalapa   = palapa_second;
                    dua.hBlink    = blink_second;
                } else {
                    dua.hPalapa   = palapa_first;
                    dua.hBlink    = blink_first;
                    timan.hPalapa = palapa_second;
                    timan.hBlink  = blink_second;
                }

                Bantugan *attacker = (who_should_go_first == 1) ? &timan : &dua;
                Bantugan *defender = (who_should_go_first == 1) ? &dua : &timan;

                if(!gameover) {
                    int can_cast = Palapa_atck && attacker->hPalapa && (attacker->mana >= PALAPA_CHARGE);
                    int skip = Palapa_atck && !can_cast;

                    if(!skip) {
                        attack(attacker, defender, Palapa_atck, sh_def, bl_def);
                    }

                    if(timan.hp <= 0 || dua.hp <= 0) {
                        gameover = 1;
                    }
                }

                // Print state after this half-turn
                isaKangBantugan("BANTUGAN TIMAN", &timan);
                isaKangBantugan("BANTUGAN DUA", &dua);

                if(gameover) {
                    dedznasyah=1;
                } else {
                // Swap gwapoooo
                who_should_go_first = (who_should_go_first == 1) ? 2 : 1;
                }
            }
        if(!dedznasyah) {
            timan.mana += REGEN;
            dua.mana   += REGEN;
            validity(&timan);
            validity(&dua);
        }
        t--;
        }

        // THE FINAL VERDICT CHAREZZ
        if(timan.hp <= 0 && dua.hp <= 0) {
            printf("DRAW! BOTH BANTUGANS SUCCUMBED AND WILL BE OFFERED TO LAKE RANAO AS SACRIFICE. MAY THE PAPANOKA MRA REWARD THEM GRACIOUSLY.\n");
        } else if(timan.hp <= 0) {
            printf("BANTUGAN TIMAN FALLS! MAY THE PAPANOKA MRA REWARD HIS COURAGE GRACIOUSLY. TO THE LAKE RANAO!\n");
        } else if(dua.hp <= 0){
            printf("BANTUGAN DUA FALLS! MAY THE PAPANOKA MRA REWARD HIS COURAGE GRACIOUSLY. TO THE LAKE RANAO!\n");
        }
    }
    return 0;
}

// functiontowns

void isaKangBantugan(const char *sinetch, Bantugan *b) {
    const char *wpnName;
    switch(b->wpn) {
        case wooden_spear:
            wpnName ="Wooden Spear";
            break;
        case silver_ax:
            wpnName = "Silver Ax";
            break;
        case diamond_scythe:
            wpnName = "Diamond Scythe";
            break;
        default:
            wpnName = "None";
            break;
    }
    const char *shldName;
    switch(b->shld) {
        case wooden:
            shldName ="Wooden Shield";
            break;
        case silver:
            shldName = "Silver Shield";
            break;
        case diamond:
            shldName = "Diamond Shield";
            break;
        default:
            shldName = "None";
            break;
    }
    printf("%s\n", sinetch);
    printf("Health: %i Mana: %i Weapon: %s Shield: %s Jade Palapa: %i Bai-a-Labi's Blink: %i\n", b->hp, b->mana, wpnName, shldName, b->hPalapa, b->hBlink);
}

void validity(Bantugan *b) {
    if(b->hp > HEALTH_BAR_FULL) b->hp = HEALTH_BAR_FULL;
    if(b->hp < 0) b->hp = 0;
    if(b->mana > MANA_FULL) b->mana = MANA_FULL;
    if(b->mana < 0) b->mana = 0;
}


void attack(Bantugan *attacker, Bantugan *defender, int palapa, int sh, int blink) {
    int cast_JP = palapa && attacker->hPalapa && (attacker->mana >= PALAPA_CHARGE);
    if(cast_JP) {
        attacker->mana = attacker->mana - PALAPA_CHARGE;
        attacker->hPalapa = 0;

        int reflection = blink && defender->hBlink && (defender->mana >= BLINK_CHARGE);
        if(reflection) {
            defender->mana = defender->mana - BLINK_CHARGE;
            defender->hBlink = 0;
        } else {
            defender->hp = defender->hp - PALAPA_PENDMG;
        }
    } else {
        int dmg_toA = 0;
        int dmg_toD = 0;

        int rawDamage = 0;
        switch(attacker->wpn) {
            case wooden_spear: rawDamage = 1; break;
            case silver_ax: rawDamage = 2; break;
            case diamond_scythe: rawDamage = 3; break;
        }

        if(!sh) {
            dmg_toD = rawDamage;
        } else {
            switch(defender->shld) {
                case wooden:
                    switch(attacker->wpn) {
                        case wooden_spear: dmg_toD = 0; break;
                        case silver_ax: dmg_toD = 1; break;
                        case diamond_scythe: dmg_toD = 3; break;
                    }
                    break;
                case silver:
                    switch(attacker->wpn) {
                        case wooden_spear: dmg_toA = 1; break;
                        case silver_ax: dmg_toD = 0; break;
                        case diamond_scythe: dmg_toD = 2; break;
                    }
                    break;
                case diamond:
                    switch(attacker->wpn) {
                        case wooden_spear: dmg_toA = 1; break;
                        case silver_ax: dmg_toA = 2; break;
                        case diamond_scythe: dmg_toD = 0; break;
                    }
                    break;
            }
        }
        defender->hp = defender->hp - dmg_toD;
        attacker->hp = attacker->hp - dmg_toA;
    }
    validity(defender);
    validity(attacker);
}
