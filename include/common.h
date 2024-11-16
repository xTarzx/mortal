#pragma once

const float PPM = 100;

#define HIP_LOWER_ANGLE (-b2_pi * 0.25f)
#define HIP_UPPER_ANGLE (b2_pi * 0.72f)

#define KNEE_LOWER_ANGLE (-b2_pi * 0.6f)
#define KNEE_UPPER_ANGLE 0.0f

#define ANKLE_LOWER_ANGLE (-b2_pi * 0.35f)
#define ANKLE_UPPER_ANGLE (b2_pi * 0.07f)

#define SHOULDER_LOWER_ANGLE (-b2_pi * 0.38f)
#define SHOULDER_UPPER_ANGLE (b2_pi * 0.99f)

#define ELBOW_LOWER_ANGLE (b2_pi * 0.005f)
#define ELBOW_UPPER_ANGLE (b2_pi * 0.85f)

#define KF_NAME_MAX_LEN 15

enum Group {
    PLAYER = 0x02,
};