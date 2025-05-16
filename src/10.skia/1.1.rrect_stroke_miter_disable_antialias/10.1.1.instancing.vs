#version 400

const float PI = 3.14159274;
const float PRECISION = 4.0;
const float NUM_TOTAL_EDGES = 16383.0;
uniform vec4 sk_RTAdjust;
uniform vec3 utessControlArgs_S0;
uniform vec4 uaffineMatrix_S0;
uniform vec2 utranslate_S0;
layout (location = 0) in vec4 pts01Attr;
layout (location = 1) in vec4 pts23Attr;
layout (location = 2) in vec2 argsAttr;
vec2 robust_normalize_diff_f2f2f2(vec2 a, vec2 b) {
    vec2 diff = a - b;
    if (diff == vec2(0.0)) {
        return vec2(0.0);
    } else {
        float invMag = 1.0 / max(abs(diff.x), abs(diff.y));
        return normalize(invMag * diff);
    }
}
vec2 unchecked_mix_f2f2f2f(vec2 a, vec2 b, float T) {
    return fma(b - a, vec2(T), a);
}
float wangs_formula_max_fdiff_p2_ff2f2f2f2f22(vec2 p0, vec2 p1, vec2 p2, vec2 p3, mat2 matrix) {
    vec2 d0 = matrix * (fma(vec2(-2.0), p1, p2) + p0);
    vec2 d1 = matrix * (fma(vec2(-2.0), p2, p3) + p1);
    return max(dot(d0, d0), dot(d1, d1));
}
float wangs_formula_conic_p2_fff2f2f2f(float _precision_, vec2 p0, vec2 p1, vec2 p2, float w) {
    vec2 C = (min(min(p0, p1), p2) + max(max(p0, p1), p2)) * 0.5;
    p0 -= C;
    p1 -= C;
    p2 -= C;
    float m = sqrt(max(max(dot(p0, p0), dot(p1, p1)), dot(p2, p2)));
    vec2 dp = fma(vec2(-2.0 * w), p1, p0) + p2;
    float dw = abs(fma(-2.0, w, 2.0));
    float rp_minus_1 = max(0.0, fma(m, _precision_, -1.0));
    float numer = length(dp) * _precision_ + rp_minus_1 * dw;
    float denom = 4.0 * min(w, 1.0);
    return numer / denom;
}
void main() {
    float NUM_RADIAL_SEGMENTS_PER_RADIAN = utessControlArgs_S0.x;
    float JOIN_TYPE = utessControlArgs_S0.y;
    float STROKE_RADIUS = utessControlArgs_S0.z;
    mat2 AFFINE_MATRIX = mat2(uaffineMatrix_S0.xy, uaffineMatrix_S0.zw);
    vec2 TRANSLATE = utranslate_S0;
    vec2 p0 = pts01Attr.xy;
    vec2 p1 = pts01Attr.zw;
    vec2 p2 = pts23Attr.xy;
    vec2 p3 = pts23Attr.zw;
    vec2 lastControlPoint = argsAttr;
    float w = -1.0;
    if (isinf(pts23Attr.w)) {
        w = p3.x;
        p3 = p2;
    }
    float numParametricSegments;
    if (w < 0.0) {
        if (p0 == p1 && p2 == p3) {
            numParametricSegments = 1.0;
        } else {
            float _0_m = wangs_formula_max_fdiff_p2_ff2f2f2f2f22(p0, p1, p2, p3, AFFINE_MATRIX);
            numParametricSegments = max(ceil(sqrt(3.0 * sqrt(_0_m))), 1.0);
        }
    } else {
        float _1_n2 = wangs_formula_conic_p2_fff2f2f2f(PRECISION, AFFINE_MATRIX * p0, AFFINE_MATRIX * p1, AFFINE_MATRIX * p2, w);
        numParametricSegments = max(ceil(sqrt(_1_n2)), 1.0);
    }
    vec2 tan0 = robust_normalize_diff_f2f2f2(p0 == p1 ? (p1 == p2 ? p3 : p2) : p1, p0);
    vec2 tan1 = robust_normalize_diff_f2f2f2(p3, p3 == p2 ? (p2 == p1 ? p0 : p1) : p2);
    if (tan0 == vec2(0.0)) {
        tan0 = vec2(1.0, 0.0);
        tan1 = vec2(-1.0, 0.0);
    }
    float edgeID = float(gl_VertexID >> 1);
    if ((gl_VertexID & 1) != 0) {
        edgeID = -edgeID;
    }
    float numEdgesInJoin = 4.0;
    float turn = determinant(mat2(p2 - p0, p3 - p1));
    float combinedEdgeID = abs(edgeID) - numEdgesInJoin;
    if (combinedEdgeID < 0.0) {
        tan1 = tan0;
        if (lastControlPoint != p0) {
            tan0 = robust_normalize_diff_f2f2f2(p0, lastControlPoint);
        }
        turn = determinant(mat2(tan0, tan1));
    }
    float cosTheta = clamp(dot(tan0, tan1), -1.0, 1.0);
    float rotation = acos(cosTheta);
    if (turn < 0.0) {
        rotation = -rotation;
    }
    float numRadialSegments;
    float strokeOutset = sign(edgeID);
    if (combinedEdgeID < 0.0) {
        numRadialSegments = numEdgesInJoin - 2.0;
        numParametricSegments = 1.0;
        p3 = (p2 = (p1 = p0));
        combinedEdgeID += numRadialSegments + 1.0;
        float sinEpsilon = 0.01;
        bool tangentsNearlyParallel = abs(turn) * inversesqrt(dot(tan0, tan0) * dot(tan1, tan1)) < sinEpsilon;
        if (!tangentsNearlyParallel || dot(tan0, tan1) < 0.0) {
            if (combinedEdgeID >= 0.0) {
                strokeOutset = turn < 0.0 ? min(strokeOutset, 0.0) : max(strokeOutset, 0.0);
            }
        }
        combinedEdgeID = max(combinedEdgeID, 0.0);
    } else {
        float maxCombinedSegments = (NUM_TOTAL_EDGES - numEdgesInJoin) - 1.0;
        numRadialSegments = max(ceil(abs(rotation) * NUM_RADIAL_SEGMENTS_PER_RADIAN), 1.0);
        numRadialSegments = min(numRadialSegments, maxCombinedSegments);
        numParametricSegments = min(numParametricSegments, (maxCombinedSegments - numRadialSegments) + 1.0);
    }
    float radsPerSegment = rotation / numRadialSegments;
    float numCombinedSegments = (numParametricSegments + numRadialSegments) - 1.0;
    bool isFinalEdge = combinedEdgeID >= numCombinedSegments;
    if (combinedEdgeID > numCombinedSegments) {
        strokeOutset = 0.0;
    }
    if (abs(edgeID) == 2.0) {
        float _2_x = fma(cosTheta, 0.5, 0.5);
        strokeOutset *= (_2_x * JOIN_TYPE) * JOIN_TYPE >= 1.0 ? inversesqrt(_2_x) : sqrt(_2_x);
    }
    vec2 tangent;
    vec2 strokeCoord;
    if (combinedEdgeID != 0.0 && !isFinalEdge) {
        vec2 A;
        vec2 B;
        vec2 C = p1 - p0;
        vec2 D = p3 - p0;
        if (w >= 0.0) {
            C *= w;
            B = 0.5 * D - C;
            A = (w - 1.0) * D;
            p1 *= w;
        } else {
            vec2 E = p2 - p1;
            B = E - C;
            A = fma(vec2(-3.0), E, D);
        }
        vec2 B_ = B * (numParametricSegments * 2.0);
        vec2 C_ = C * (numParametricSegments * numParametricSegments);
        float lastParametricEdgeID = 0.0;
        float maxParametricEdgeID = min(numParametricSegments - 1.0, combinedEdgeID);
        float negAbsRadsPerSegment = -abs(radsPerSegment);
        float maxRotation0 = (1.0 + combinedEdgeID) * abs(radsPerSegment);
        for (int _0_exp = 4;_0_exp >= 0; --_0_exp) {
            float testParametricID = lastParametricEdgeID + exp2(float(_0_exp));
            if (testParametricID <= maxParametricEdgeID) {
                vec2 testTan = fma(vec2(testParametricID), A, B_);
                testTan = fma(vec2(testParametricID), testTan, C_);
                float cosRotation = dot(normalize(testTan), tan0);
                float maxRotation = fma(testParametricID, negAbsRadsPerSegment, maxRotation0);
                maxRotation = min(maxRotation, PI);
                if (cosRotation >= cos(maxRotation)) {
                    lastParametricEdgeID = testParametricID;
                }
            }
        }
        float parametricT = lastParametricEdgeID / numParametricSegments;
        float lastRadialEdgeID = combinedEdgeID - lastParametricEdgeID;
        float angle0 = acos(clamp(tan0.x, -1.0, 1.0));
        angle0 = tan0.y >= 0.0 ? angle0 : -angle0;
        float radialAngle = fma(lastRadialEdgeID, radsPerSegment, angle0);
        tangent = vec2(cos(radialAngle), sin(radialAngle));
        vec2 norm = vec2(-tangent.y, tangent.x);
        float a = dot(norm, A);
        float b_over_2 = dot(norm, B);
        float c = dot(norm, C);
        float discr_over_4 = max(b_over_2 * b_over_2 - a * c, 0.0);
        float q = sqrt(discr_over_4);
        if (b_over_2 > 0.0) {
            q = -q;
        }
        q -= b_over_2;
        float _5qa = (-0.5 * q) * a;
        vec2 root = abs(fma(q, q, _5qa)) < abs(fma(a, c, _5qa)) ? vec2(q, a) : vec2(c, q);
        float radialT = root.y != 0.0 ? root.x / root.y : 0.0;
        radialT = clamp(radialT, 0.0, 1.0);
        if (lastRadialEdgeID == 0.0) {
            radialT = 0.0;
        }
        float T = max(parametricT, radialT);
        vec2 ab = unchecked_mix_f2f2f2f(p0, p1, T);
        vec2 bc = unchecked_mix_f2f2f2f(p1, p2, T);
        vec2 cd = unchecked_mix_f2f2f2f(p2, p3, T);
        vec2 abc = unchecked_mix_f2f2f2f(ab, bc, T);
        vec2 bcd = unchecked_mix_f2f2f2f(bc, cd, T);
        vec2 abcd = unchecked_mix_f2f2f2f(abc, bcd, T);
        float u = fma(w - 1.0, T, 1.0);
        float v = (w + 1.0) - u;
        float uv = fma(v - u, T, u);
        if (T != radialT) {
            tangent = w >= 0.0 ? robust_normalize_diff_f2f2f2(bc * u, ab * v) : robust_normalize_diff_f2f2f2(bcd, abc);
        }
        strokeCoord = w >= 0.0 ? abc / uv : abcd;
    } else {
        tangent = combinedEdgeID == 0.0 ? tan0 : tan1;
        strokeCoord = combinedEdgeID == 0.0 ? p0 : p3;
    }
    vec2 ortho = vec2(tangent.y, -tangent.x);
    strokeCoord += ortho * (STROKE_RADIUS * strokeOutset);
    vec2 devCoord = AFFINE_MATRIX * strokeCoord + TRANSLATE;
    gl_Position = vec4(devCoord, 0.0, 1.0);
    gl_Position = vec4(gl_Position.xy * sk_RTAdjust.xz + gl_Position.ww * sk_RTAdjust.yw, 0.0, gl_Position.w);
}