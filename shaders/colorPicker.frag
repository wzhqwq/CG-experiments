#version 330 core
#define PI 3.1415926535897932384626433832795
#define INV_SQRT_3 0.577350269189626

in vec2 uv;
out vec4 color;

uniform vec3 hsv;

vec3 hsv_to_rgb(float h, float s, float v) {
    float c = v * s;
    h = h * 6.0;
    float x = c * (1.0 - abs(mod(h, 2.0) - 1.0));
    vec3 result;
    if (0.0 <= h && h < 1.0) {
        result = vec3(c, x, 0.0);
    } else if (1.0 <= h && h < 2.0) {
        result = vec3(x, c, 0.0);
    } else if (2.0 <= h && h < 3.0) {
        result = vec3(0.0, c, x);
    } else if (3.0 <= h && h < 4.0) {
        result = vec3(0.0, x, c);
    } else if (4.0 <= h && h < 5.0) {
        result = vec3(x, 0.0, c);
    } else if (5.0 <= h && h < 6.0) {
        result = vec3(c, 0.0, x);
    } else {
        result = vec3(0.0, 0.0, 0.0);
    }
    result.rgb += v - c;
    return result;
}

void main() {
    float d = length(uv);
    vec2 ringPos = vec2(0.47 * sin(hsv.x * PI * 2), 0.47 * cos(hsv.x * PI * 2));
    vec2 rectPos = vec2(hsv.y * 0.6 - 0.3, hsv.z * 0.6 - 0.3);
    float ringDist = length(ringPos - uv);
    float rectDist = length(rectPos - uv);
    
    if (ringDist < 0.03) {
        if (ringDist > 0.025) {
            color = vec4(1.0, 1.0, 1.0, 1.0);
        }
        else {
            color = vec4(hsv_to_rgb(hsv.x, 1.0, 1.0), 1.0);
        }
        return;
    }
    if (rectDist < 0.03) {
        if (rectDist > 0.025) {
            float c = hsv.z < 0.5 ? 1.0f : 0.0f;
            color = vec4(c, c, c, 1.0f);
        }
        else {
            color = vec4(hsv_to_rgb(hsv.x, hsv.y, hsv.z), 1.0);
        }
        return;
    }
    if (abs(uv.x) < 0.3 && abs(uv.y) < 0.3) {
        // draw rect
        color = vec4(hsv_to_rgb(hsv.x, uv.x / 0.6 + 0.5, uv.y / 0.6 + 0.5), 1.0);
    }
    else if (d > 0.44 && d < 0.5) {
        // draw ring
        float angle = atan(uv.x, uv.y) / PI / 2;
        if (angle < 0.0) angle += 1.0;
        color = vec4(hsv_to_rgb(angle, 1.0, 1.0), 1.0);
    }
    else {
        color = vec4(0.0, 0.0, 0.0, 0.0);
    }
}
