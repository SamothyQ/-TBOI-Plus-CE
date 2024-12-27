#include <sys/util.h>
#include <graphx.h>
#include <keypadc.h>
#include <math.h>

#include "gfx/gfx.h"

#define START_X ((GFX_LCD_WIDTH - (isaac1_width * 3)) / 2)
#define START_Y ((GFX_LCD_HEIGHT - (isaac1_height * 3)) / 2)
#define ENEMY_TYPES 6
#define BOSS_TYPES 6
#define ITEM_TYPES 16
#define PICKUP_TYPES 7

const bool rockFormations[8][91] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,},
                                    { 0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      1,1,0,0,0,0,0,0,0,0,0,1,1,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      1,1,0,0,0,0,0,0,0,0,0,1,1,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,},
                                    { 0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,1,1,1,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,1,1,1,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,},
                                    { 0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,1,0,1,0,0,0,1,0,1,0,0,
                                      0,0,1,0,1,0,0,0,1,0,1,0,0,
                                      0,0,1,0,1,0,0,0,1,0,1,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,},
                                    { 0,0,0,0,0,1,0,1,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      1,0,0,0,0,0,0,0,0,0,0,0,1,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      1,0,0,0,0,0,0,0,0,0,0,0,1,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,1,0,1,0,0,0,0,0,},
                                    {0,0,0,1,0,0,0,0,0,1,0,0,0,
                                    0,0,0,1,0,0,0,0,0,1,0,0,0,
                                    0,0,0,1,0,0,0,0,0,1,0,0,0,
                                    0,0,0,0,0,0,0,0,0,0,0,0,0,
                                    0,0,0,1,0,0,0,0,0,1,0,0,0,
                                    0,0,0,1,0,0,0,0,0,1,0,0,0,
                                    0,0,0,1,0,0,0,0,0,1,0,0,0,},
                                    { 0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,1,0,1,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,
                                      0,0,0,0,0,0,0,0,0,0,0,0,0,},
                                    { 0,0,0,1,0,0,0,0,0,1,0,0,0,
                                      1,0,0,0,0,0,0,0,0,0,0,0,1,
                                      0,0,0,0,0,0,1,0,0,0,0,0,0,
                                      0,0,1,0,0,0,0,0,0,0,1,0,0,
                                      0,0,0,0,0,0,1,0,0,0,0,0,0,
                                      1,0,0,0,0,0,0,0,0,0,0,0,1,
                                      0,0,0,1,0,0,0,0,0,1,0,0,0,} };
const bool enemyFormations[8][91] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0, 
                                  0,0,0,0,0,0,0,0,0,0,0,0,0,
                                  0,0,0,0,0,0,0,0,0,0,0,0,0,
                                  0,0,0,0,0,0,0,0,0,0,0,0,0,
                                  0,0,0,0,0,0,0,0,0,0,0,0,0,
                                  0,0,0,0,0,0,0,0,0,0,0,0,0,
                                  0,0,0,0,0,0,0,0,0,0,0,0,0,}, 
                                { 0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,1,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,}, 
                                { 0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,1,0,0,0,0,0,1,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,}, 
                                { 0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,1,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,1,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,}, 
                                { 0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,1,0,0,1,0,0,1,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,},
                                { 0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,1,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,1,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,1,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,},
                                { 0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,1,0,0,0,0,0,0,0,1,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                1,0,0,0,0,0,0,0,0,0,0,0,1,},
                                { 0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,1,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,1,0,0,0,0,0,1,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,0,0,0,0,0,0,0,0,0,0,1,0,}};



const uint8_t rocksPerFormation[8] = {0, 4, 6, 12, 8, 12, 2, 12};
float x = START_X;
float y = START_Y;
float centerX;
float centerY;
int tearCooldown;
uint8_t tearQueue;
uint8_t map[100];
uint8_t mapAttempted[100];
bool mapVisited[100];
bool mapCleared[100];
uint8_t curRoomCount;
uint8_t mapQueue;
uint8_t room = 44;
uint8_t enemyCount = 0;
const gfx_sprite_t *spritesByType[ENEMY_TYPES] = {gaper, fly, maw, maggot, globin, vis};
const uint8_t enemyShootingByType[ENEMY_TYPES] = {0, 0, 1, 0, 0, 2};
const double speedsByType[ENEMY_TYPES] = {1.15, 0.75, 0.25, 0.55, 1.25, 0.6};
const int healthByType[ENEMY_TYPES] = {10, 3, 20, 15, 33, 25};
const float bossHealthByType[BOSS_TYPES] = {110, 300, 595, 450, 632.5, 650};
const uint8_t enemyMovementByType[ENEMY_TYPES] = {0, 0, 0, 1, 0, 1};
float statDMG = 3.5;
float statTEARS = 22;
float statSPEED = 2.1;
float statRANGE = 100;
uint8_t statCOINS = 0;
uint8_t statBOMBS = 1;
uint8_t statKEYS = 0;
float velocLagMult = 1;
uint8_t redHeartContainers = 6;
uint8_t redHearts = 6;
uint8_t soulHearts = 0;
bool eternalHeart = false;
bool isaacInvinsible = false;
uint8_t IFrames = 0;
int globalTimer = 0;
uint8_t eTearQueue = 0;
const gfx_sprite_t *itemSpritesByType[ITEM_TYPES] = {dinner, woodenspoon, wirecoathanger, momslipstick, catoninetails, magicmush, spoonbender, polyphemus, twentytwenty, toughlove, lokishorns, luckyfoot, thevirus, thedsix, bookofbelial, yumheart};
bool pickedUpTreasureItem = false;
bool pickedUpBossItem = false;
uint8_t floorBossItem;
bool heldItems[ITEM_TYPES];
uint8_t heldActiveItem = 0;
uint8_t itemPickupCooldown = 0;
float itemCharges = 6;
const float maxChargesByType[3] = {6, 3, 4};
float tempBoostDMG = 0;
float netDMG = 3.5;
const gfx_sprite_t *pickupSpritesByType[PICKUP_TYPES] = {halfheart, fullheart, soulheart, penny, nickel, key, bomb};
uint8_t pickupCount = 0;
const uint8_t floorColors[6] = {3, 3, 8, 8, 9, 9};
uint8_t level = 0;
uint8_t lazerCount = 0;
bool gameWon = false;

uint8_t CountSetBits(uint8_t n);
void DrawBG();
void PlrTearUpdate();
void InitTear(uint8_t direction, uint8_t n);
void MapGen();
uint8_t CountNeighbors(uint8_t array[100], uint8_t index);
void ResetMap();
void DisplayUI();
void MoveRooms(int direction);
void InitEnemy(int x, int y, uint8_t type, int atkTimer);
void EnemyUpdate();
void SeeRoomsAround();
float PythagDistance(float x1, float x2, float y1, float y2);
void TearSplash(uint8_t n);
void DisplayHealth();
void BossUpdate();
void InitBoss(int x, int y, uint8_t type);
void TakeDamage();
void InitEnemyTear(int x, int y, float direction, int shotSpeed, uint8_t n);
void EnemyTearUpdate();
void EnemyTearSplash(uint8_t n);
void InitFloor(bool floorIncrease);
void ItemUpdate(uint8_t id, int x, int y, bool isTreasureRoom);
void UseItem(uint8_t id);
float min(float a, float b);
uint8_t randomTreasureItemGen(uint8_t exception);
uint8_t randomBossItemGen(uint8_t exception);
void DisplayStats();
void DrawRocks(uint8_t formation);
void CalculateLag();
bool RockCollision(int x, int y, int radius);
void InitPickup(int x, int y, uint8_t type);
void PickupUpdate();
uint8_t randomPickupGen();
void InitLazer(float x, float y, bool isEnemy, uint8_t d);
void LazerSplash(uint8_t n);
void LazerUpdate();
void InitCreep(int x, int y, int r, uint8_t color, uint8_t ticks, bool isEnemy);
void CreepUpdate();
void UpdateIsaac();
void DrawTrapdoor();
bool EnemyDamage(uint8_t n, float damage);

struct PlrTear {
    float x; //X position on the screen
    float y; //Y position on the screen
    uint8_t range; //Range the tear has left in frames
    bool exists; //Whether or not it should be calculated or rendered
    uint8_t d; //Direction
    float tearSize; //Size offset of the tear
    float dmgMult; //Multiplier of damage
    float xVeloc;
    float yVeloc;
};

struct Enemy {
    float x;
    float y;
    float hp;
    uint8_t type;
    bool exists;
    int atkTimer;
    uint8_t state;
    int stateTimer;
    float xVeloc;
    float yVeloc;
};

struct Boss {
    float x;
    float y;
    float hp;
    float xVeloc;
    float yVeloc;
    uint8_t type;
    int atkTimer;
    bool exists;
    uint8_t state;
    float angle;
    bool tangible;
};

struct EnemyTear {
    float x;
    float y;
    float d;
    uint8_t range;
    float shotSpeed;
    bool exists;
};

struct Pickup {
    int x;
    int y;
    uint8_t type;
    uint8_t room;
    bool exists;
};

struct Lazer {
    float x;
    float y;
    uint8_t ticks;
    bool isEnemy;
    uint8_t d;
    bool exists;
};

struct Creep {
    int x;
    int y;
    int r;
    uint8_t ticks;
    uint8_t color;
    bool exists;
    bool isEnemy;
};

struct Boss roomBoss;
struct PlrTear pTears[10];
struct Enemy enemies[8];
struct EnemyTear eTears[10];
struct Pickup floorPickups[20];
struct Lazer lazers[10];
struct Creep roomCreep;


int main(void)
{

    /* Initialize the graphics */
    gfx_Begin();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    /* Draw to the offscreen buffer */
    gfx_SetDrawBuffer();


    //Select a seed
    gfx_FillScreen(2);
    gfx_SetTextFGColor(1);
    gfx_PrintStringXY("Press f1 To Start...", 5, 20);
    gfx_PrintStringXY("Made by Samothy (u/SamothyBoiledBois)", 5, 169);
    gfx_PrintStringXY("Using the CE C Toolchain (not by me)", 5, 189);
    gfx_PrintStringXY("https://ce-programming.github.io", 5, 209);
    gfx_BlitBuffer();

    int seed = 0;
    while (kb_Data[1] != kb_Yequ) {
        kb_Scan();
        seed += 1;
    }
    srand(seed);

    /* Set the palette for the sprites */
    gfx_FillScreen(1);
    gfx_SetTransparentColor(0);

    InitFloor(false);
    CalculateLag();

    /* Copy the buffer to the screen */
    /* Same as gfx_Blit(gfx_buffer) */
    gfx_BlitBuffer();

    do
    {
        if (!gameWon) {
            DrawRocks((map[room] - 1) / 8);
            DrawTrapdoor();
            CreepUpdate();
            PlrTearUpdate();
            EnemyTearUpdate();
            EnemyUpdate();
            LazerUpdate();
            BossUpdate();
            PickupUpdate();
            UpdateIsaac();

            //Update the items if they exist
            if (map[room] > 64 && map[room] < 81 && !pickedUpTreasureItem) {
                ItemUpdate(map[room] - 65, 159, 153, true);
            }
            if ((map[room] == 81 || map[room] == 82) && !pickedUpBossItem && roomBoss.exists == false) {
                ItemUpdate(floorBossItem, 159, 203, false);
            }


            /* Copy the buffer to the screen */
            gfx_BlitBuffer();

            //Update timers
            tearCooldown += 1;
            globalTimer += 1;
            if (isaacInvinsible == true) {
                IFrames -= 1;
                if (!IFrames) {
                    isaacInvinsible = false;
                }
            }
            if (itemPickupCooldown) {
                itemPickupCooldown -= 1;
            }
        } else {
            kb_Scan();
            gfx_FillScreen(2);
            gfx_PrintStringXY("congratualtiossns", 5, 20);
            gfx_PrintStringXY("press sto-> now", 5, 209);
            gfx_BlitBuffer();
        }
    } while (kb_Data[2] != kb_Sto  && (soulHearts || redHearts));

    /* End graphics drawing */
    gfx_End();
    return 0;
}

//======================
/* GENERAL FUNCTIONS */
//======================

float PythagDistance(float x1, float x2, float y1, float y2) { //Returns the distance between two points given their coordinates
    float a = fabsf(x1 - x2);
    float b = fabsf(y1 - y2);
    return sqrt((a*a) + (b*b));
}

void InitFloor(bool floorIncrease) {
    /* Draw the main sprite and background*/
    room = 44;
    level += 1 * floorIncrease;
    MapGen();
    SeeRoomsAround();
    DrawBG();
    DisplayUI();
    UpdateIsaac();
    MoveRooms(0);

    if (level > 5) {
        gameWon = true;
    }

    pickedUpTreasureItem = false;
    pickedUpBossItem = false;
    floorBossItem = randomBossItemGen(255);
    for (int i = 0; i < 20; i += 1) {
        floorPickups[i].exists = false;
    }
    pickupCount = 0;
    x = START_X;
    y = START_Y;
}

float min(float a, float b) {
    if (a > b) {
        return b;
    } else {
        return a;
    }
}

float max(float a, float b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

void CalculateLag() {
    float currentRockCount;
    if (map[room] < 65) {
        currentRockCount = rocksPerFormation[(map[room] - 1) / 8];
    } else {
        currentRockCount = 0;
    }
    velocLagMult = 1 + (0.3 * enemyCount) + ((0.05 + 0.001 * (netDMG - 3.5)) * tearQueue) + (0.25 * roomBoss.exists) + (0.29 * (currentRockCount / 12)) + (0.25 * lazerCount) + (0.05 * eTearQueue);
}

//==================================
/* FUNCTIONS FOR ISAACS MOVEMENT */
//==================================

void UpdateIsaac() {
    float plrVeloc;
    centerX = x + 14;
    centerY = y + 36;
    netDMG = statDMG + tempBoostDMG;

    kb_key_t arrows;

    /* Scan the keypad to update kb_Data */
    kb_Scan();

    /* Get the arrow key statuses */
    arrows = kb_Data[7];

    gfx_SetColor(floorColors[level]);
    gfx_FillRectangle_NoClip(x, y, 27, 48);

    const uint8_t shootingOrders[4][4] = { {0, 1, 2, 3}, {1, 2, 3, 0}, {2, 3, 0, 1}, {3, 0, 1, 2} };
    if (tearCooldown > statTEARS / velocLagMult) { //Check if the tear cooldown is over
        uint8_t lokiHornLuck = rand() % 8;
        uint8_t shootingDirection;
        for (int i = 0; i < 1 + 3 * (heldItems[10] && (lokiHornLuck == 1)); i += 1) {
            bool tearFired = true;
            if (kb_Data[4] & kb_Stat) {
                shootingDirection = 1;
            } else if (kb_Data[2] & kb_Alpha) {
                shootingDirection = 3;
            } else if (kb_Data[1] & kb_Mode) {
                shootingDirection = 0;
            } else if (kb_Data[3] & kb_GraphVar) {
                shootingDirection = 2;
            } else {
                tearFired = false;
            }
            if (tearFired) {
                InitTear(shootingOrders[shootingDirection][i], tearQueue);
            }
        }
    }
    /* Check if any movement keys are pressed */
    if (arrows) {
        if (CountSetBits(arrows) == 2) { //If the player is holding 2 arrows
            plrVeloc = sqrt(2); //Speed is set to sqrt(2)
        } else {
            plrVeloc = 2; //Speed is set to 2
        }

        plrVeloc *= velocLagMult;

        /* Do different directions depending on the keypress */
        if ((arrows & kb_Right) && centerX < 306 && !RockCollision(centerX + plrVeloc, centerY, 10))
        {
            x += plrVeloc;
            if (centerX > 297 && room % 10 != 9 && mapCleared[room]) {
                MoveRooms(1);
            }
        }
        if ((arrows & kb_Left) && centerX > 15 && !RockCollision(centerX - plrVeloc, centerY, 10))
        {
            x -= plrVeloc;
            if (centerX < 23 && room % 10 != 0 && mapCleared[room]) {
                MoveRooms(-1);
            }
        }
        if ((arrows & kb_Down) && centerY < 227 && !RockCollision(centerX, centerY + plrVeloc, 10))
        {
            y += plrVeloc;
            if (centerY > 218 && room / 10 != 9 && mapCleared[room]) {
                MoveRooms(10);
            }
        }
        if ((arrows & kb_Up)  && centerY > 104 && !RockCollision(centerX, centerY - plrVeloc, 10))
        {
            y -= plrVeloc;
            if (centerY < 109 && room % 10 != 0 && mapCleared[room]) {
                MoveRooms(-10);
            }
        }   
    }

    if (kb_Data[1] & kb_Graph && heldActiveItem && itemCharges >= maxChargesByType[heldActiveItem - 13]) {
        UseItem(heldActiveItem);
    }

    /* Render the sprite */
    if (!isaacInvinsible || globalTimer % 4) {
        gfx_ScaledTransparentSprite_NoClip(isaac1, x, y, 3, 3);
    }
}

uint8_t CountSetBits(uint8_t n) { //Counts the amount of bits set in an 8-bit integer
    if (n == 0) {
        //Stop function if all bits are counted
        return 0;
    } else {
        //Add 1 if the right-most bit is set
        return (n & 1) + CountSetBits(n >> 1);
    }
}

//=========================================
/* FUNCTIONS FOR DRAWING THE BACKGROUND */
//=========================================

void DrawBG() { //Draws the main shapes behind the sprites
    gfx_FillScreen(floorColors[level]);
    gfx_SetColor(2);
    gfx_FillRectangle_NoClip(0, 0, 320, 67);
}

void DisplayUI () {
    for (int x = 0; x < 10; x += 1) {
        for (int y = 0; y < 10; y += 1) {
            uint8_t roomIndex = (y * 10) + x;
            uint8_t roomType = map[roomIndex];

            if (roomType && (mapVisited[roomIndex] || heldItems[11])) {
                if (roomType < 65 || roomType == 255) {
                    gfx_SetColor(1);
                } else if (roomType < 81) {
                    gfx_SetColor(5);
                } else if (roomType < 83) {
                    gfx_SetColor(0);
                }

                gfx_FillRectangle_NoClip(1 + (x * 5), 1 + (y * 5), 4, 4);
            }
        }
    }

    DisplayHealth();
    
    gfx_SetTextFGColor(1);
    gfx_SetTextBGColor(2);
    gfx_PrintStringXY("f5", 198, 3);
    if (heldActiveItem) {
        gfx_SetColor(2);
        gfx_FillRectangle_NoClip(194, 10, 27, 35);
        gfx_ScaledTransparentSprite_NoClip(itemSpritesByType[heldActiveItem], 194, 10, 3, 3);
        gfx_SetColor(6);
        float chargeBarLength = min((itemCharges / maxChargesByType[heldActiveItem - 13]) * 27, 27);
        gfx_FillRectangle_NoClip(194, 40, chargeBarLength, 5);
    }

    DisplayStats();

    gfx_SetColor(6);
    gfx_FillRectangle_NoClip(1 + ((room % 10) * 5), 1 + ((room / 10) * 5), 4, 4);
}

void DisplayStats() {
    gfx_SetTextFGColor(0);
    gfx_PrintStringXY("DMG", 52, 1);
    gfx_SetTextFGColor(4);
    gfx_PrintStringXY("TRS", 52, 16);
    gfx_SetTextFGColor(6);
    gfx_PrintStringXY("SPD", 52, 31);
    gfx_SetTextFGColor(5);
    gfx_PrintStringXY("RNG", 52, 46);

    netDMG = statDMG + tempBoostDMG;
    gfx_SetTextFGColor(1);
    float statDisplays[4] = {netDMG * 10, 6000 / statTEARS, (statSPEED * 100) / 2.1, (statRANGE * 100) / 16.6};
    for (int i = 0; i < 4; i += 1) {
        gfx_SetTextXY(80, 1 + (15 * i));
        gfx_PrintInt(statDisplays[i], 3);
    }

    gfx_ScaledTransparentSprite_NoClip(penny, 112, 0, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(bomb, 112, 20, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(key, 112, 40, 2, 2);
    uint8_t pickupDisplays[4] = {statCOINS, statBOMBS, statKEYS};
    for (int i = 0; i < 3; i += 1) {
        gfx_SetTextXY(128, 4 + i * 20);
        gfx_PrintInt(pickupDisplays[i], 2);
    }
}

//================================
/* FUNCTIONS FOR ISAAC'S TEARS */
//================================

void PlrTearUpdate() { //Updates a given tear from the player
    for (int n = 0; n < 10; n += 1) {
        if (pTears[n].exists) {
            float xPos = pTears[n].x;
            float yPos = pTears[n].y;
            bool notSplashed = false;
            float tearSize = pTears[n].tearSize;
            uint8_t shortestDist;
            float enemyDist;


            //Cover up existing tear
            gfx_SetColor(floorColors[level]);
            gfx_FillCircle(xPos, yPos, 5 + pTears[n].tearSize);

            //Calculate the new location of the tear
            if (pTears[n].range) { //If the tear has any range left
                xPos += pTears[n].xVeloc * velocLagMult * 2;
                yPos += pTears[n].yVeloc * velocLagMult * 2;
                if (pTears[n].range % 15 == 0 && heldItems[6] == true && !mapCleared[room]) {
                    float shortestDistValue = 10000000;
                    for (int i = 0; i < 8; i += 1) {
                        if (enemies[i].exists) {
                            enemyDist = PythagDistance(xPos, enemies[i].x, yPos, enemies[i].y);
                            if (enemyDist < shortestDistValue) {
                                shortestDist = i;
                                shortestDistValue = enemyDist;
                            }
                        }
                    }
                    if (roomBoss.exists) {
                        enemyDist = PythagDistance(xPos, roomBoss.x, yPos, roomBoss.y);
                        if (enemyDist < shortestDistValue) {
                            shortestDist = 9;
                        }
                    }
                    float angle;
                    if (shortestDist == 9) {
                        angle = atan2(roomBoss.x - xPos, roomBoss.y - yPos);
                    } else {
                        angle = atan2(enemies[shortestDist].x - xPos, enemies[shortestDist].y - yPos);
                    }
                    pTears[n].xVeloc = sin(angle);
                    pTears[n].yVeloc = cos(angle);
                }
                if (xPos > 5 + tearSize && xPos < 314 - tearSize && yPos > 72 + tearSize && yPos < 234 - tearSize && !RockCollision(xPos, yPos, 5 + tearSize)) {
                    notSplashed = true;
                }
                pTears[n].range -= 1;
            }

            //Shift the tear queue if the tear splashed.
            if (!notSplashed) {
                TearSplash(n);
            } else {
                gfx_SetColor(4);
                gfx_FillCircle(xPos, yPos, 5 + tearSize);
                pTears[n].x = xPos;
                pTears[n].y = yPos;
            }
        }
    }
}

void InitTear(uint8_t direction, uint8_t n) { //Adds a new tear to the screen
    for (int i = 0; i < 1 + 1 * (heldItems[8]); i += 1) {
        if (tearQueue < 10 - i) {
            float adjustedX = centerX;
            float adjustedY = centerY - 14;
            uint8_t adjustedN = n + i;
            if ((direction == 0 || direction == 2) && heldItems[8]) {
                adjustedX += -6 + 12 * i;
            } else if (heldItems[8]){
                adjustedY += -6 + 12 * i;
            }
            pTears[adjustedN].x = adjustedX;
            pTears[adjustedN].y = adjustedY;
            pTears[adjustedN].d = direction;
            pTears[adjustedN].exists = true;
            pTears[adjustedN].range = statRANGE;
            pTears[adjustedN].dmgMult = 1;
            pTears[adjustedN].xVeloc = (direction == 1) - (direction == 3);
            pTears[adjustedN].yVeloc = (direction == 2) - (direction == 0);
            if (heldItems[9] && rand() % 10 == 1) {
                pTears[adjustedN].dmgMult = 3.2;
            }
            pTears[adjustedN].tearSize = 0.5 * ((netDMG * pTears[adjustedN].dmgMult) - 3.5);
            tearQueue += 1;
            CalculateLag();
        }
    }
    tearCooldown = 0;
}

void TearSplash(uint8_t n) {
    gfx_SetColor(floorColors[level]);
    gfx_FillCircle(pTears[n].x, pTears[n].y, 5 + pTears[n].tearSize);
    
    for (int i = 0; i + n < 9; i += 1) {
            //Shift everything after the splashed tear left one.
            pTears[n + i] = pTears[n + i + 1];
        }

    //Edit the tear queue
    tearQueue -= 1;
    CalculateLag();

    //Delete the last tear
    pTears[9].exists = false;
}

//=================================
/* FUNCTIONS FOR THE MAP SYSTEM */
//=================================

void MapGen() { //Generates a new map
    ResetMap();
    bool mapSuccess = false;
    uint8_t nextRoom;
    uint8_t nextDirection;
    uint8_t totalRoomCount = 7 + (rand() % 3);
    map[44] = 255;
    mapAttempted[44] = true;
    mapCleared[44] = true;

    while (!mapSuccess) {
        if (CountNeighbors(mapAttempted, mapQueue) >= 3) {
            if (mapQueue == 44) {
                ResetMap();
            } else {
                mapQueue = 44;
                for (int i = 0; i < 100; i += 1) {
                    mapAttempted[i] = false;
                }
            }
        }

        nextDirection = rand() % 4;

        if (nextDirection == 0 && mapQueue < 90) {
            nextRoom = mapQueue + 10;
        } else if (nextDirection == 1 && mapQueue % 10 != 9) {
            nextRoom = mapQueue + 1;
        } else if (nextDirection == 2 && mapQueue > 9) {
            nextRoom = mapQueue - 10;
        } else if (!(mapQueue % 10)) {
            nextRoom = mapQueue - 1;
        }

        if (map[nextRoom] == 0) {
            if (CountNeighbors(map, nextRoom) < 2) {
                if (curRoomCount < totalRoomCount) {
                    //Map not windy enough.... me sad...
                    if (!(rand() % 2)) {
                        mapQueue = nextRoom;
                        map[nextRoom] = 1 + rand() % 64;
                        curRoomCount += 1;
                        if (curRoomCount == totalRoomCount / 2) {
                            mapQueue = 44;
                            map[nextRoom] = 65 + randomTreasureItemGen(255);
                            //map[nextRoom] = 79;
                        }
                    }
                }
            }
        }

        mapAttempted[nextRoom] = true;
        kb_Scan();

        //It might not generate a functioning map, but at least I won't freeze again.
        //I've probably taken out the calculator's battery like 200 times now
        if (curRoomCount >= totalRoomCount || kb_Data[6] & kb_Clear) {
            mapSuccess = true;
            map[mapQueue] = 81 + (rand() % 2);
        }
    }
}

uint8_t CountNeighbors(uint8_t array[100], uint8_t index) { //Counts how many of the adjacent squares in an array are set to true, with a given index
    uint8_t i = 0;

    if ((index % 10 != 9) && array[index + 1]) {
        i += 1;
    } 
    if ((index % 10 != 0) && array[index - 1]) {
        i += 1;
    }
    if ((index < 90) && array[index + 10]) {
        i += 1;
    }
    if ((index > 9) && array[index - 10]) {
        i += 1;
    }

    return i;
} 

void ResetMap() { //Resets the map creation
    for (int i = 0; i < 100; i += 1) {
        map[i] = 0;
        mapAttempted[i] = false;
        mapVisited[i] = false;
        mapCleared[i] = false;
    }
    curRoomCount = 1;
    mapQueue = 44;
    map[44] = 255;
    mapCleared[44] = true;
}

void MoveRooms(int direction) {
    if (map[room + direction] && (fabsf(centerX - 160) < 14 || fabsf(centerY - 154) < 14)) {
        room += direction;
        
        if (centerX > 295) {
            x = 0;
            y = 117;
        } else if (centerX < 25) {
            x = 293;
            y = 117;
        }
        if (centerY > 215) {
            y = 68;
            x = 145;
        } else if (centerY < 109) {
            y = 192;
            x = 145;
        }

        for (int i = 0; i < 8; i += 1) {
            enemies[i].exists = false;
        }
        enemyCount = 0;
        if (!mapCleared[room]) {
            if (map[room] == 81 || map[room] == 82) {
                InitBoss(160, 154, (rand() % 2) + ((level / 2) * 2));
            } else if (map[room] < 65) {
                for (int gridX = 0; gridX < 13; gridX += 1) {
                    for (int gridY = 0; gridY < 7; gridY += 1) {
                        if (enemyFormations[map[room] % 8][gridX + (gridY * 13)]) {
                            InitEnemy((gridX * 24) + 16,(gridY * 24) + 81, rand() % 2 + ((level / 2) * 2), 25);
                        }
                    }
                }
                if (map[room] % 8 == 0) {
                    mapCleared[room] = true;
                }
            } else {
                mapCleared[room] = true;
            }
        }

        tempBoostDMG = 0;

        SeeRoomsAround();
        DrawBG();
        DisplayUI();

        for(int i = 0; i < 10; i += 1) {
            pTears[i].exists = false;
        }
        tearQueue = 0;
        CalculateLag();
    }
}

void SeeRoomsAround() {
    const int8_t offsets[4] = {1, 10, -1, -10};

    for (int i = 0; i < 4; i += 1) {
        mapVisited[room + offsets[i]] = true;
    }
    mapVisited[room] = true;
}

//=============================
/* FUNCTIONS FOR THE ENEMIES*/
//=============================

void InitEnemy(int x, int y, uint8_t type, int atkTimer) {
    //50 kilobites isnt enough for this shit. do better sam
    if (enemyCount < 8) {
        enemies[enemyCount].exists = true;
        enemies[enemyCount].x = x;
        enemies[enemyCount].y = y;
        enemies[enemyCount].type = type;
        enemies[enemyCount].atkTimer = atkTimer;
        enemies[enemyCount].hp = healthByType[type];
        enemies[enemyCount].xVeloc = 0;
        enemies[enemyCount].yVeloc = 0;
        enemies[enemyCount].state = 0;
        enemies[enemyCount].stateTimer = 0;
        enemyCount += 1;
        CalculateLag();
    }
}

void EnemyUpdate() {
    for (int n = 0; n < 8; n += 1) {
        if (enemies[n].exists) {
            uint8_t type = enemies[n].type;
            float newX = enemies[n].x;
            float newY = enemies[n].y;
            float xVeloc = enemies[n].xVeloc;
            float yVeloc = enemies[n].yVeloc;
            bool enemyDied = false;

            gfx_SetColor(floorColors[level]);
            gfx_FillRectangle_NoClip(enemies[n].x - 15, enemies[n].y - 37, 31, 51);

            if (enemies[n].stateTimer) {
                enemies[n].stateTimer -= 1;
            } else if (enemies[n].state) {
                if (enemyShootingByType[type] == 2) {
                    InitLazer(enemies[n].x, enemies[n].y, true, enemies[n].state - 1);
                }
                enemies[n].state = 0;
            } 

            if (enemies[n].atkTimer < 2) {
                float angle;
                if (!enemyMovementByType[type]) {
                    //Trigonometry is for fucking nerds
                    angle = atan2(centerX - enemies[n].x, centerY - enemies[n].y);
                } else {
                    angle = (rand() % 16) * 0.3926991; //angle in 22.5 degree increments
                }
                if (!enemyMovementByType[type] || !(rand() % 90) || enemies[n].atkTimer == 1) {
                    xVeloc = sin(angle) * velocLagMult;
                    yVeloc = cos(angle) * velocLagMult;
                }
                if (!enemies[n].state) {
                    newX = enemies[n].x + xVeloc * speedsByType[type]; 
                    newY = enemies[n].y + yVeloc * speedsByType[type];
                }

                //Shooting code
                if (globalTimer % 40 == 1 && enemyShootingByType[type] == 1) {
                    InitEnemyTear(enemies[n].x, enemies[n].y, angle, 2, eTearQueue);
                }
                if (enemyShootingByType[type] == 2 && !(enemies[n].state)) {
                    if (fabsf(centerX - enemies[n].x) < 5) {
                        if (centerY < enemies[n].y) {
                            enemies[n].state = 1;
                        } else {
                            enemies[n].state = 3;
                        }
                        enemies[n].stateTimer = 40;
                    } else if (fabsf(centerY - enemies[n].y) < 5) {
                        if (centerX < enemies[n].x) {
                            enemies[n].state = 4;
                        } else {
                            enemies[n].state = 2;
                        }
                        enemies[n].stateTimer = 40;
                    }
                }
            }
            if (enemies[n].atkTimer) {
                enemies[n].atkTimer -= 1;
            }
            
            if (PythagDistance(enemies[n].x, centerX, enemies[n].y, centerY) < 28) {
                newX = enemies[n].x;
                newY = enemies[n].y;
                if (heldItems[12] && !isaacInvinsible) {
                    if (EnemyDamage(n, 30)) {
                        enemyDied = true;
                    }
                }
                TakeDamage();
            }

            for (int i = 0; i < 10; i += 1) {
                if (PythagDistance(enemies[n].x, pTears[i].x, enemies[n].y, pTears[i].y) < 21 + pTears[i].tearSize && pTears[i].exists && enemies[n].exists) {
                    uint8_t d = pTears[i].d;
                    float dmgMult = pTears[i].dmgMult;
                    
                    TearSplash(i);
                    if (EnemyDamage(n, netDMG * dmgMult)) {
                        enemyDied = true;
                    }
                    if (d == 0) {
                        newY -= 7;
                    } else if (d == 1) {
                        newX += 7;
                    } else if (d == 2) {
                        newY += 7;
                    } else if (d == 3) {
                        newX -= 7;
                    }
                }
            }
            
            if (!enemyDied) {
                if (newX < 306 && newX > 14 && !RockCollision(newX, enemies[n].y, 10)) {
                    enemies[n].x = newX;
                } 
                if (newY < 226 && newY > 103 && !RockCollision(enemies[n].x, newY, 10)) {
                    enemies[n].y = newY;
                }
                
                enemies[n].xVeloc = xVeloc;
                enemies[n].yVeloc = yVeloc;
                if (enemies[n].exists && (!enemies[n].state || globalTimer % 2)) {
                    gfx_ScaledTransparentSprite_NoClip(spritesByType[type], enemies[n].x - 15, enemies[n].y - 37, 3, 3);
                }
            }
        }
    }
}

bool EnemyDamage(uint8_t n, float damage) {
    if (enemies[n].hp > damage) {
        enemies[n].hp -= damage;
        return false;
    } else {
        for (int i = 0; i + n < 7; i += 1) {
            enemies[n + i] = enemies[n + i + 1];
        }
        enemies[7].exists = false;
        enemyCount -= 1;
        CalculateLag();
        if (enemyCount == 0 && map[room] < 81) {
            mapCleared[room] = true;
            itemCharges += 1;
            DisplayUI();
            if (rand() % 100 < 78) {
                InitPickup(159, 153, randomPickupGen());
            }
        }
        return true;
    }
}

//=========================
//* FUNCTIONS FOR HEALTH*/
//=========================

void DisplayHealth() {
    gfx_SetColor(2);
    gfx_FillRectangle_NoClip(GFX_LCD_WIDTH - 95, 25, 87, 32);

    gfx_SetTextFGColor(0);
    gfx_SetTextBGColor(2);
    gfx_PrintStringXY("-LIFE-", GFX_LCD_WIDTH - 75, 10);
    
    //Red Heart Containers
    gfx_SetColor(7);
    for(int i = 0; i < (redHeartContainers / 2); i += 1) {
        gfx_FillRectangle_NoClip((GFX_LCD_WIDTH - 95) + ((i % 6) * 15), 25 + 20 * (i / 6), 12, 12);
    }

    //Red Hearts
    gfx_SetColor(0);
    for(int i = 0; i < redHearts; i += 1) {
        gfx_FillRectangle_NoClip((GFX_LCD_WIDTH - 95) + ((i % 12) * 6) + ((i / 2) * 3 - (18 * (i > 11))), 25 + 20 * (i / 12), 6, 12);
    }

    //Soul Hearts
    gfx_SetColor(4);
    for (int i = 0; i < soulHearts; i += 1) {
        int heartPos = i + redHeartContainers;
        gfx_FillRectangle_NoClip((GFX_LCD_WIDTH - 95) + ((heartPos % 12) * 6) + ((heartPos / 2) * 3 - (18 * (heartPos > 11))), 25 + 20 * (heartPos / 12), 6, 12);
    }
}

void TakeDamage() {
    if (isaacInvinsible == false) {
        isaacInvinsible = true;
        IFrames = 80;
        redHearts -= 1 * (!soulHearts);
        soulHearts -= 1 * (soulHearts > 0);
        DisplayHealth();
    }
}

//=========================
//* FUNCTIONS FOR BOSSES*/
//=========================

void BossUpdate() {
    if (roomBoss.exists) {
        float x = roomBoss.x;
        float y = roomBoss.y;
        float angle = roomBoss.angle;

        gfx_SetColor(floorColors[level]);
        gfx_FillRectangle_NoClip(x - 25, y - 34, 51, 51);

        //COLLISION
        if (roomBoss.tangible) {
            for (int i = 0; i < 10; i += 1) {
                if (PythagDistance(x, pTears[i].x, y, pTears[i].y) < 30 + pTears[i].tearSize && pTears[i].exists) {
                    gfx_SetColor(2);
                    gfx_FillRectangle_NoClip(52, 61, 172, 3);
                    float dmgMult = pTears[i].dmgMult;
                    if (roomBoss.hp > netDMG * dmgMult) {
                        roomBoss.hp -= netDMG * dmgMult;
                        gfx_SetColor(0);
                        gfx_FillRectangle_NoClip(52, 61, (roomBoss.hp / bossHealthByType[roomBoss.type]) * 172, 3);
                    } else {
                        roomBoss.exists = false;
                        mapCleared[room] = true;
                        itemCharges += 1;
                        DisplayUI();
                        for (int i = 0; i < rand() % 4; i += 1) {
                            InitPickup(189 - rand() % 60, 162 - rand() % 60, rand() % 2);
                        }
                    }
                    TearSplash(i);
                }
            }
        }
        roomBoss.atkTimer += 1;

        if (roomBoss.type == 0) { //DUKE OF FLIES   
            if (x + roomBoss.xVeloc < 293 && x + roomBoss.xVeloc > 25) {
                x += roomBoss.xVeloc * velocLagMult;
            } else {
                roomBoss.xVeloc *= -1;
            }
            if (y + roomBoss.yVeloc * velocLagMult > 101 && y + roomBoss.yVeloc * velocLagMult < 222) {
                y += roomBoss.yVeloc * velocLagMult;
            } else {
                roomBoss.yVeloc *= -1;
            }
        
            roomBoss.x = x;
            roomBoss.y = y;

            if (roomBoss.atkTimer > 256) {
                roomBoss.atkTimer = 0;
                for (int i = 0; i < 1 + (rand() % 3); i += 1) {
                    InitEnemy(x + (rand() % 30), y + (rand() % 30), 1, 0);
                }
            }

            if (roomBoss.exists && (roomBoss.atkTimer < 226 || !(globalTimer % 4))) {
                gfx_ScaledTransparentSprite_NoClip(dukeofflies, x - 25, y - 34, 3, 3);
            }
        } else if (roomBoss.type == 1) { //DINGLE
            if (roomBoss.atkTimer == 128 && roomBoss.state == 0) {
                if (rand() % 2) {
                    roomBoss.state = 1;
                } else {
                    for (int i = 0; i < 3; i += 1) {
                        InitEnemyTear(x, y, angle + (0.5 * i) - 0.5, 4, eTearQueue);
                    }
                }
                roomBoss.atkTimer = 0;
            }
            if ((roomBoss.state == 0 && roomBoss.atkTimer == 98) || (roomBoss.state == 1 && roomBoss.atkTimer % 60 == 40)) {
                angle = atan2(centerX - x, centerY - y);
                roomBoss.xVeloc = sin(angle) * 4;
                roomBoss.yVeloc = cos(angle) * 4;
                roomBoss.angle = angle;
            }
            if (roomBoss.state == 1) {
                if (roomBoss.atkTimer % 60 < 25) {
                    x += roomBoss.xVeloc * velocLagMult;
                    y += roomBoss.yVeloc * velocLagMult;
                }
                if (roomBoss.atkTimer == 180) {
                    roomBoss.atkTimer = 0;
                    roomBoss.state = 0;
                }
                if (x < 25 || x > 293) {
                    x = roomBoss.x;
                }
                if (y < 101 || y > 222) {
                    y = roomBoss.y;
                }
            }

            roomBoss.x = x;
            roomBoss.y = y;

            if (roomBoss.exists && (roomBoss.state == 1 || roomBoss.atkTimer < 98 || globalTimer % 4)) {
                gfx_ScaledTransparentSprite_NoClip(dingle, roomBoss.x - 25, roomBoss.y - 34, 3, 3);
            }
        } else if (roomBoss.type == 2) { //GURDY
            if (roomBoss.atkTimer > 100) {
                roomBoss.atkTimer = 0;
                bool attack = rand() % 2;
                if (attack) {
                    uint8_t gurdySpawnAmount = 2 + (rand() % 2);
                    uint8_t gurdyEnemySpawned = 1 + (rand() % 3);

                    for (uint8_t i = 0; i < gurdySpawnAmount; i += 1) {
                        InitEnemy(x - 50 + (rand() % 100), y - 59 + (rand() % 60), gurdyEnemySpawned, 10);
                    }
                } else {
                    for (uint8_t i = 0; i < 5; i += 1) {
                        if (centerY > y + 35 || centerY < y - 44) {
                            InitEnemyTear(x, y, 5.236 + (i * 0.524) + (3.142 * (centerY < y)), 3, eTearQueue);
                        } else {
                            InitEnemyTear(x, y, 0.785 + (i * 0.393) + (3.142 * (centerX < x)), 3, eTearQueue);
                        }
                    }
                }
            }
            
            if (roomBoss.exists && (roomBoss.atkTimer < 70 || globalTimer % 4)) {
                gfx_ScaledTransparentSprite_NoClip(gurdy, roomBoss.x - 25, roomBoss.y - 34, 3, 3);
            }
        } else if(roomBoss.type == 3) { //PEEP
            if (roomBoss.atkTimer == 100 && !roomBoss.state) {
                roomBoss.atkTimer = 0;
                if (roomBoss.y > 127 && roomBoss.y < 179 && roomBoss.x > 60 && roomBoss.x < 259 && rand() % 3) {
                    InitCreep(roomBoss.x, roomBoss.y, 60, 5, 80, true);
                    for (int i = 0; i < 6; i += 1) {
                        InitEnemyTear(roomBoss.x, roomBoss.y, 1.0472 * i, 4, eTearQueue);
                    }
                } else {
                    roomBoss.tangible = false;
                    roomBoss.state = 1;
                }
            }

            if (roomBoss.state) {
                if (roomBoss.atkTimer == 30) {
                    roomBoss.x = centerX;
                    roomBoss.y = centerY;
                } else if (roomBoss.atkTimer == 60) {
                    roomBoss.tangible = true;
                    roomBoss.state = 0;
                    roomBoss.atkTimer = 0;
                    for (int i = 0; i < 8; i += 1) {
                        InitEnemyTear(roomBoss.x, roomBoss.y, 0.7854 * i, 4, eTearQueue);
                    }
                }
            }

            if (roomBoss.exists && roomBoss.tangible && (roomBoss.atkTimer < 70 || globalTimer % 4)) {
                gfx_ScaledTransparentSprite_NoClip(peep, roomBoss.x - 25, roomBoss.y - 34, 3, 3);
            }
        } else if (roomBoss.type == 4) { //MONSTRO II
            if (!roomBoss.state) {
                if (roomBoss.atkTimer > 60) {
                    if (fabsf(centerY - roomBoss.y) < 27 && rand() % 2) {
                        InitLazer(roomBoss.x, roomBoss.y, true, 1 + 2*(centerX < roomBoss.x));
                    } else if (rand() % 2) {
                        roomBoss.state = 1;
                        if (rand() % 2) {
                            for (int i = 0; i < 2 + rand() % 3; i += 1) {
                                InitEnemy(x, y, 1 + rand() % 3, 10);
                            }
                        }
                    } else {
                        roomBoss.state = 2;
                        roomBoss.tangible = false;
                    }
                    roomBoss.atkTimer = 0;
                } else if (roomBoss.atkTimer == 50) {
                    angle = atan2(centerX - x, centerY - y);
                    roomBoss.xVeloc = sin(angle) * 3;
                    roomBoss.yVeloc = cos(angle) * 3;
                    roomBoss.angle = angle;
                }
            } else if (roomBoss.state == 1) {
                x += roomBoss.xVeloc * velocLagMult;
                y += roomBoss.yVeloc * velocLagMult;
                if (x > 24 && x < 294) { //make a generalized version for all bosses pls
                    roomBoss.x = x;
                }
                if (y > 100 && y < 223) {
                    roomBoss.y = y;
                }
                if (roomBoss.atkTimer > 25) {
                    roomBoss.atkTimer = 0;
                    roomBoss.state = 0;
                }
            } else if (roomBoss.state == 2) {
                if (roomBoss.atkTimer == 35) {
                    roomBoss.x = centerX;
                    roomBoss.y = centerY; //Can drop Monstro II out of bounds, fix this pls
                } else if (roomBoss.atkTimer == 80) {
                    roomBoss.tangible = true;
                    roomBoss.state = 0;
                    roomBoss.atkTimer = 0;
                    for (int i = 0; i < 8; i += 1) {
                        InitEnemyTear(roomBoss.x, roomBoss.y, 0.7854 * i, 4, eTearQueue);
                    }
                }
            }

            if (roomBoss.exists && (roomBoss.atkTimer < 30 || globalTimer % 4) && roomBoss.tangible) {
                gfx_ScaledTransparentSprite_NoClip(monstrotwo, roomBoss.x - 25, roomBoss.y - 34, 3, 3);
            }
        } else if (roomBoss.type == 5) { //LOKI
            if (!roomBoss.state) {
                if (roomBoss.atkTimer == 60) {
                    roomBoss.atkTimer = 0;
                    if (!(rand() % 4)) {
                        for (int i = 0; i < 8; i += 1) {
                            InitEnemyTear(roomBoss.x, roomBoss.y, 0.7854 * i, 4, eTearQueue);
                        }
                    } else if (rand() % 3) {
                        roomBoss.state = 1;
                    } else if (rand() % 2) {
                        bool teleportGenerated = false;
                        int teleportX;
                        int teleportY;
                        while (!teleportGenerated) {
                            teleportX = 26 + (rand() % 268);
                            teleportY = 101 + (rand() % 121);
                            if (PythagDistance(centerX, centerY, teleportX, teleportY) > 70) {
                                teleportGenerated = true;
                            }
                        }
                        x = teleportX;
                        y = teleportY;
                    } else {
                        for (uint8_t i = 0; i < 3; i += 1) {
                            InitEnemy(roomBoss.x, roomBoss.y, 1 + rand() % 3, 10);
                        }
                    }
                }
                angle = atan2(centerX - x, centerY - y);
                roomBoss.xVeloc = sin(angle);
                roomBoss.yVeloc = cos(angle);
                roomBoss.angle = angle;
                x += roomBoss.xVeloc * velocLagMult * 0.8;
                y += roomBoss.yVeloc * velocLagMult * 0.8;
            } else if (roomBoss.state == 1) {
                if (roomBoss.atkTimer % 20 == 1) {
                    for (uint8_t i = 0; i < 4; i += 1) {
                        InitEnemyTear(roomBoss.x, roomBoss.y, 1.571 * i + (0.7854 * (roomBoss.atkTimer / 20)), 4, eTearQueue);
                    }
                }
                if (roomBoss.atkTimer == 60) {
                    roomBoss.atkTimer = 0;
                    roomBoss.state = 0;
                }
            }

            if (x < 293 && x > 26) {
                roomBoss.x = x;
            }
            if (y > 101 && y < 222) {
                roomBoss.y = y;
            }

            if (roomBoss.exists && (roomBoss.atkTimer < 40 || roomBoss.state || globalTimer % 4)) {
                gfx_ScaledTransparentSprite_NoClip(loki, roomBoss.x - 25, roomBoss.y - 34, 3, 3);
            }
        }
        //DAMAGE
        if (PythagDistance(x, centerX, y, centerY) < 38 && roomBoss.exists && roomBoss.tangible) {
            if (heldItems[12] && !isaacInvinsible) {
                gfx_SetColor(2);
                gfx_FillRectangle_NoClip(52, 61, 172, 3);
                if (roomBoss.hp > 30) {
                    roomBoss.hp -= 30;
                    gfx_SetColor(0);
                    gfx_FillRectangle_NoClip(52, 61, (roomBoss.hp / bossHealthByType[roomBoss.type]) * 172, 3);
                } else {
                    roomBoss.exists = false;
                    mapCleared[room] = true;
                    for (int i = 0; i < rand() % 4; i += 1) {
                        InitPickup(189 - rand() % 60, 162 - rand() % 60, rand() % 2);
                    }
                    itemCharges += 1;
                    DisplayUI();
                }
            }
            TakeDamage();
            x = roomBoss.x;
            y = roomBoss.y;
        }
    }
}

void InitBoss(int x, int y, uint8_t type) {
    roomBoss.exists = true;
    roomBoss.x = x;
    roomBoss.y = y;
    roomBoss.type = type;
    roomBoss.xVeloc = 1;
    roomBoss.yVeloc = 1;
    roomBoss.atkTimer = 0;
    roomBoss.state = 0;
    roomBoss.hp = bossHealthByType[type];
    roomBoss.tangible = true;
    gfx_SetColor(0);
    gfx_FillRectangle_NoClip(52, 61, 172, 3);
}

//============================
//* FUNCTIONS FOR ENEMY TEARS
//============================

void EnemyTearUpdate() { //Updates a given tear from the player
    for (int n = 0; n < 10; n += 1) {
        if (eTears[n].exists) {
            float direction = eTears[n].d;
            int xPos = eTears[n].x;
            int yPos = eTears[n].y;
            float xVeloc;
            float yVeloc;
            bool notSplashed = false;

            //Cover up existing tear
            gfx_SetColor(floorColors[level]);
            gfx_FillCircle(xPos, yPos, 5);

            //Calculate the new location of the tear
            if (eTears[n].range) { //If the tear has any range left
                eTears[n].range -= 1;
                notSplashed = true;
                
                xVeloc = sin(direction) * eTears[n].shotSpeed;
                yVeloc = cos(direction) * eTears[n].shotSpeed;
                xPos += xVeloc * velocLagMult;
                yPos += yVeloc * velocLagMult;

                if (xPos > 314 || xPos < 5 || yPos > 234 || yPos < 72 || RockCollision(xPos, yPos, 5)) {
                    notSplashed = false;
                }

                if (PythagDistance(xPos, centerX, yPos, centerY) < 18) {
                    TakeDamage();
                    notSplashed = false;
                }
            }

            //Shift the tear queue if the tear splashed.
            if (!notSplashed) {
                EnemyTearSplash(n);
            } else {
                gfx_SetColor(0);
                gfx_FillCircle(xPos, yPos, 5);
                eTears[n].x = xPos;
                eTears[n].y = yPos;
            }
        }
    }
}

void InitEnemyTear(int x, int y, float direction, int shotSpeed, uint8_t n) { //Adds a new tear to the screen
    if (eTearQueue < 10) {
        eTears[n].x = x;
        eTears[n].y = y;
        eTears[n].d = direction;
        eTears[n].exists = true;
        eTears[n].range = 100;
        eTears[n].shotSpeed = shotSpeed;
        eTearQueue += 1;
    }
    CalculateLag();
}

void EnemyTearSplash(uint8_t n) {
    gfx_SetColor(floorColors[level]);
    gfx_FillCircle(eTears[n].x, eTears[n].y, 5);
    
    for (int i = 0; i + n < 9; i += 1) {
            //Shift everything after the splashed tear left one.
            eTears[n + i] = eTears[n + i + 1];
        }

    //Edit the tear queue
    eTearQueue -= 1;
   
    //Delete the last tear
    eTears[9].exists = false;
    CalculateLag();
}

//=====================
//FUNCTIONS FOR ITEMS
//=====================

void ItemUpdate(uint8_t id, int x, int y, bool isTreasureRoom) {
    gfx_SetColor(floorColors[level]);
    gfx_FillRectangle_NoClip(x - 14, y - 14, 27, 27);

    if (PythagDistance(x, centerX, y, centerY) < 26 && !itemPickupCooldown) {
        if (isTreasureRoom) {
            pickedUpTreasureItem = true;
        } else {
            pickedUpBossItem = true;
        }
        if (id < 9) {
            switch (id) {
                case 0 : //Dinner
                    if (redHeartContainers + soulHearts < 25) {
                        redHeartContainers += 2;
                        redHearts += 4;
                        if (redHearts > redHeartContainers) {
                            redHearts = redHeartContainers;
                        }
                    }
                    break;
                case 1 : //Wooden Spoon
                    statSPEED += 0.6;
                    if (statSPEED > 4) {
                        statSPEED = 4;
                    }
                    break;
                case 2 : //Wire Coat Hanger
                    statTEARS -= 4.5;
                    if (statTEARS < 8.6) {
                        statTEARS = 8.6;
                    }
                    break;
                case 3 : //Mom's Lipstick
                    statRANGE += 57;
                    break;
                case 4 : //Cat o' Nine Tails
                    statDMG += 1;
                    break;
                case 5 : //Magic Mush
                    if (redHeartContainers + soulHearts < 25) {
                        redHeartContainers += 2;
                        redHearts = redHeartContainers;
                    }
                    statDMG += 0.3;
                    statDMG *= 1.5;
                    statRANGE += 38;
                    statSPEED += 0.6;
                    break;
                case 7: //Polyphemus
                    statDMG += 4;
                    statDMG *= 2;
                    statTEARS *= 2.38;
                    break;
                case 8: //20 20
                    statDMG *= 0.8;
                    break;
            }
        }
        if (id > 4 || id == 3) {
            heldItems[id] = true;
        }
        if (id > 12 && id < 16) {
            if (heldActiveItem) {
                if (isTreasureRoom) {
                    pickedUpTreasureItem = false;
                    map[room] = 65 + heldActiveItem;
                } else {
                    pickedUpBossItem = false;
                    floorBossItem = heldActiveItem;
                }
            }
            heldActiveItem = id;
        }
        itemPickupCooldown = 100;
        DisplayUI();
    } 

    if ((!pickedUpTreasureItem && isTreasureRoom) || (!isTreasureRoom && !pickedUpBossItem)) {
        gfx_ScaledTransparentSprite_NoClip(itemSpritesByType[id], x - 14, y - 14, 3, 3);
    }
}

void UseItem(uint8_t id) {
    if (id == 15) { //Yum Heart
        redHearts += 2;
        if (redHearts > redHeartContainers) {
            redHearts = redHeartContainers;
        }
    } else if (id == 14) { //Book of Belial
        tempBoostDMG = 2;
    } else if (id == 13) { //The D6
        if (map[room] > 64 && map[room] < 81) {
            map[room] = 65 + randomTreasureItemGen(map[room] - 65);
        } else if (map[room] == 81 || map[room] == 82) {
            floorBossItem = randomBossItemGen(floorBossItem);
        }
    }
    itemCharges = 0;
    DisplayUI();
}

uint8_t randomTreasureItemGen(uint8_t exception) {
    bool itemGenerated = false;
    uint8_t testItem;
    while (!itemGenerated) {
        uint8_t randomItem = rand() % 100;
        if (randomItem < 22) {
            testItem = rand() % 4;
        } else if (randomItem < 30) {
            testItem = 4;
        } else if (randomItem < 40) {
            testItem = 5 + rand () % 4;
        } else if (randomItem < 80) {
            testItem = 9 + rand() % 4;
        } else {
            testItem = 13 + rand() % 3;
        }
        if (!heldItems[testItem] && testItem != exception) {
            itemGenerated = true;
        }
    }
    return testItem;

}

uint8_t randomBossItemGen(uint8_t exception) {
    bool itemGenerated = false;
    uint8_t testItem;
    while (!itemGenerated) {
        uint8_t randomItem = rand() % 100;
        if (randomItem < 75) {
            testItem = rand() % 3;
        } else {
            testItem = 4;
        }
        if (!heldItems[testItem] && testItem != exception) {
            itemGenerated = true;
        }
    }
    return testItem;
}

//============================
//FUNCTIONS FOR DRAWING ROCKS
//============================

void DrawRocks(uint8_t formation) {
    if (globalTimer % 2 && map[room] < 65) {
        for (int x = 0; x < 13; x += 1) {
            for (int y = 0; y < 7; y += 1) {
                if (rockFormations[formation][x + (y * 13)]) {
                    gfx_ScaledTransparentSprite_NoClip(rock, 4 + (x * 24), 69 + (y * 24), 3, 3);
                }
            }
        }
    }
}

bool RockCollision(int x, int y, int radius) {
    if (map[room] > 64) {
        return false;
    }
    int gridYPoints[2] = {(y - 69 + radius) / 24, (y - 69 - radius) / 24};
    int gridXPoints[2] = {(x - 4 - radius) / 24, (x - 4 + radius) / 24};
    for (int i = 0; i < 4; i += 1) {
        if (rockFormations[(map[room] - 1) / 8][gridXPoints[i / 2] + (gridYPoints[i % 2] * 13)]) {
            return true;
        }
    }
    return false;
}

void DrawTrapdoor() {
    //Draw trapdoor (every frame unfortunately)
    if ((map[room] == 81 || map[room] == 82) && roomBoss.exists == false) {
        gfx_SetColor(2);
        gfx_FillRectangle_NoClip(149, 162, 20, 20);
        if (centerX > 149 && centerX < 169 && centerY > 162 && centerY < 182) {
            InitFloor(true);
        }
    }
}

//======================
//FUNCTIONS FOR PICKUPS
//======================

void InitPickup(int x, int y, uint8_t type) {
    if (pickupCount < 20) {
        floorPickups[pickupCount].exists = true;
        floorPickups[pickupCount].type = type;
        floorPickups[pickupCount].x = x;
        floorPickups[pickupCount].y = y;
        floorPickups[pickupCount].room = room;
        pickupCount += 1;
    }
}

void PickupUpdate() {
    for (int n = 0; n < 20; n += 1) {
        if (floorPickups[n].exists && floorPickups[n].room == room) {
            int spriteX = floorPickups[n].x - 11;
            int spriteY = floorPickups[n].y - 11;
            bool pickedUp = false;
            gfx_SetColor(floorColors[level]);
            gfx_FillRectangle_NoClip(spriteX, spriteY, 22, 22);

            if (PythagDistance(floorPickups[n].x, centerX, floorPickups[n].y, centerY) < 23) {
                pickedUp = true;

                switch (floorPickups[n].type) {
                    case 0 :
                        redHearts += 1;
                        if (redHearts > redHeartContainers) {
                            redHearts = redHeartContainers;
                            pickedUp = false;
                        }
                        break;
                    case 1 :
                        if (redHeartContainers == redHearts) {
                            pickedUp = false;
                        }
                        redHearts += 2;
                        if (redHearts > redHeartContainers) {
                            redHearts = redHeartContainers;
                        }
                        break;
                    case 2 :
                        if (redHeartContainers + soulHearts < 23) {
                            soulHearts += 2;
                        } else {
                            pickedUp = false;
                        }
                        break;
                    case 3 :
                        statCOINS += 1;
                        if (statCOINS > 99) {
                            statCOINS = 99;
                        }
                        break;
                    case 4 :
                        statCOINS += 5;
                        if (statCOINS > 99) {
                            statCOINS = 99;
                        }
                        break;
                    case 5 :
                        statKEYS += 1;
                        if (statKEYS > 99) {
                            statKEYS = 99;
                        }
                        break;
                    case 6 :
                        statBOMBS += 1;
                        if (statBOMBS > 99) {
                            statBOMBS = 99;
                        }
                        break;
                }
                if (pickedUp) {
                    floorPickups[n].exists = false;
                    pickupCount -= 1;
                    DisplayUI();
                }
            }

            if (floorPickups[n].exists) {
                gfx_ScaledTransparentSprite_NoClip(pickupSpritesByType[floorPickups[n].type], spriteX, spriteY, 3, 3);
            }
        }
    }
}

uint8_t randomPickupGen() {
    uint8_t pickupSeed = rand() % 78;
    
    if (pickupSeed < 12) {
        return 3;
    } else if (pickupSeed < 18) {
        return 4;
    } else if (pickupSeed < 29) {
        return 1;
    } else if (pickupSeed < 33) {
        return 0;
    } else if (pickupSeed < 36) {
        return 2;
    } else if (pickupSeed < 60) {
        return 5;
    } else {
        return 6;
    }
}

//=======================
//FUNCTIONS FOR LAZERS
//=======================

void InitLazer(float x, float y, bool isEnemy, uint8_t d) {
    lazers[lazerCount].x = x;
    lazers[lazerCount].y = y;
    lazers[lazerCount].ticks = 24;
    lazers[lazerCount].exists = true;
    lazers[lazerCount].isEnemy = isEnemy;
    lazers[lazerCount].d = d;
    lazerCount += 1;
}

void LazerUpdate() {
    for (int n = 0; n < 10; n += 1) {
        if (lazers[n].exists) {
            float x = lazers[n].x;
            float y = lazers[n].y;
            uint8_t d = lazers[n].d;
            bool isHorizontal = d % 2;
            
            bool endPtFound = false;
            int testX = x;
            int testY = y;
            int testXPlaceholder = x;
            int testYPlaceholder = y;
            uint8_t i = 0;
            while(!endPtFound && i < 14) {
                testXPlaceholder += (24 * (d == 1)) - (24 * (d == 3));
                testYPlaceholder += (24 * (d == 2)) - (24 * (!d));
                if (!RockCollision(testXPlaceholder, testYPlaceholder, 8)) {
                testX = testXPlaceholder;
                testY = testYPlaceholder;
                } else {
                    endPtFound = true;
                }
                i += 1;
            }
            
            int lazerPointsX[2] = {
                ((x - 8) * !isHorizontal) + (max(testX, 0) * (d == 3)) + (x * (d == 1)), 
                ((x + 8) * !isHorizontal) + (x * (d == 3)) + (min(testX, 319) * (d == 1))
            };
            int lazerPointsY[2] = {
                ((y - 8) * isHorizontal) + (max(testY, 67) * (!d)) + (y * (d == 2)),
                ((y + 8) * isHorizontal) + (y * (!d)) + (min(testY, 239) * (d == 2))
            };

            int width = lazerPointsX[1] - lazerPointsX[0];
            int height = lazerPointsY[1] - lazerPointsY[0];

            gfx_SetColor(floorColors[level]);
            gfx_FillRectangle_NoClip(lazerPointsX[0], lazerPointsY[0], width, height);

            bool notSplashed = true;
            lazers[n].ticks -= 1;
            if (lazers[n].ticks < 1) {
                LazerSplash(n);
                notSplashed = false;
            }

            if (lazers[n].isEnemy && gfx_CheckRectangleHotspot(lazerPointsX[0], lazerPointsY[0], width, height, centerX - 12, centerY - 12, 24, 24)) {
                TakeDamage();
            }

            if (notSplashed) {
                gfx_SetColor(0);
                gfx_FillRectangle_NoClip(lazerPointsX[0], lazerPointsY[0], width, height);
            }
        }
    }
}

void LazerSplash(uint8_t n) {
    lazers[n].exists = false;
    for (int i = 0; i + n < 9; i += 1) {
        lazers[n + i] = lazers[n + i + 1];
    }
    lazers[9].exists = false;
    lazerCount -= 1;
}

//====================
//FUNCTIONS FOR CREEP
//====================

void CreepUpdate() {
    if (roomCreep.exists) {
        gfx_SetColor(floorColors[level]);
        gfx_FillCircle_NoClip(roomCreep.x, roomCreep.y, roomCreep.r);

        if (roomCreep.ticks) {
            roomCreep.ticks -= 1;
        } else {
            roomCreep.exists = false;
        }

        if (PythagDistance(roomCreep.x, roomCreep.y, centerX, centerY) < roomCreep.r) {
            TakeDamage();
        }

        if (roomCreep.exists) {
            gfx_SetColor(roomCreep.color);
            gfx_FillCircle_NoClip(roomCreep.x, roomCreep.y, roomCreep.r);
        }
    }
}

void InitCreep(int x, int y, int r, uint8_t color, uint8_t ticks, bool isEnemy) {
    gfx_SetColor(floorColors[level]);
    gfx_FillCircle_NoClip(roomCreep.x, roomCreep.y, roomCreep.r);

    roomCreep.x = x;
    roomCreep.y = y;
    roomCreep.r = r;
    roomCreep.color = color;
    roomCreep.ticks = ticks;
    roomCreep.exists = true;
    roomCreep.isEnemy = isEnemy;
}
