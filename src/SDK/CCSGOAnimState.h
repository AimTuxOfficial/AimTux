#pragma once

class CCSGOAnimState
{
public:
    char pad_0008[128]; //0x0000
    float lastAnimUpdateTime; //0x0080
    int32_t lastAnimUpdateFrame; //0x0084
    float eyePitch; //0x0088
    float yaw; //0x008C
    float pitch; //0x0090
    float goalFeetYaw; //0x0094
    float currentFeetYaw; //0x0098
    float absMovementDirection; //0x009C  Movement direction on a compass, North = 0, East = 90, South = 180...
    float lastAbsMovementDirection; //0x00A0 ^^^^^ for last tick
    float leanAmount; //0x00A4
    char pad_00A8[4]; //0x00A8
    float feetCycle; //0x00AC Progress from 0.0-1.0 of the legs moving animation.
    float feetYawRate; //0x00B0 How fast to play feetCycle ( walking = slower )
    char pad_00B4[4]; //0x00B4
    float duckProgress; //0x00B8 Progress 0.0-1.0, 0.0 = standing, 1.0 = fully crouched. Also used for jumping. Counts backwards from 1.0 for jumps
    float landingAnimationTimeLeftUntilDone; //0x00BC Adds some time when landing animation starts.
    char pad_00C0[4]; //0x00C0
    Vector origin; //0x00C4
    Vector lastOrigin; //0x00D0
    float velocityX; //0x00DC Speeds on axis
    float velocityY; //0x00E0 ^^^^^^^^^^
    char pad_00E4[4]; //0x00E4
    float currentDirectionX; //0x00E8 -1.0 to 1.0. West is 1.0, East is -1.0. North and South are both 0
    float currentDirectionY; //0x00EC -1.0 to 1.0. North is -1.0, South is 1.0. East and West are both 0
    char pad_00F0[4]; //0x00F0
    float lastKnownDirectionX; //0x00F4 Same as its counterpart above, but this is saved until the next update
    float lastKnownDirectionY; //0x00F8 ^^^^^^^^^^^^^^^^^^^^^^^
    char pad_00FC[4]; //0x00FC
    float horizontalVelocity; //0x0100 Affected by slopes. ( got 240 with knife on a hill )
    float verticalVelocity; //0x0104. Goes up when jumping, negative when falling
    float speed; //0x0108 0.0 -> 1.0, how fast you are going; 1.0 = full speed.
    float feetShuffleSpeed; //0x010C // 0.0-2.0 (approx)
    float feetShuffleSpeed2; //0x0110 // 0.0-3.0 (approx)
    float timeSinceStartedMoving; //0x0114 Jumping and Crouching do not affect these
    float timeSinceStoppedMoving; //0x0118 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    bool onGround; //0x011C True if on ground (do I need to type this?)
    bool inJumpRecoveryAnim; //0x011D True if you're doing one of the retarded knee buckling animations
    char pad_011E[10]; //0x011E
    float heightBeforeJump; //0x0128 Updated right when you jump
    char pad_012C[4]; //0x012C
    float runningAccelProgress; //0x0130 0 - 1.0, Only affected by Running, reaches 1.0 when you are at full speed (ex: 250 w/ knife )
    char pad_0134[68]; //0x0134
    char unkown[572];// Overall Size should be 0x3B0(+4), padding the end here.
}; //Size: 0x0178
