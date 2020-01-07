extern "C" {

    const char *getType() {
        return ("MOB");
    }

    const char *getName() {
        return ("Mob");
    }

    const char *getTexture() {
        return ("assets/monster.png");
    }

    unsigned int getDamage() {
        return (20);
    }

    unsigned int getAmmunitions() {
        return (3);
    }

    float getFireRate() {
        return (2.f);
    }

    float getReload() {
        return (5.f);
    }

    const char *getMissileName() {
        return ("Missile.so");
    }

    unsigned int getSizeX() {
        return (41);
    }

    unsigned int getSizeY() {
        return (47);
    }

    unsigned int getHp() {
        return (50);
    }

    unsigned int getReward() {
        return (100);
    }

    unsigned int getSpeed() {
        return (2);
    }

}
