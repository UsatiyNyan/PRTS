#pragma once

#include <fmt/format.h>
#include <istream>
#include <vector>

namespace task1 {
enum class TraxId : unsigned char {
    HEADING = 5,
    PITCH = 24,
    ROLL = 25,
    HEADING_STATUS = 79,
    QUATERNION = 77,
    TEMPERATURE = 7,
    DISTORTION = 8,
    CAL_STATUS = 9,
    ACCEL_X = 21,
    ACCEL_Y = 22,
    ACCEL_Z = 23,
    MAG_X = 27,
    MAG_Y = 28,
    MAG_Z = 29,
    GYRO_X = 74,
    GYRO_Y = 75,
    GYRO_Z = 76
};

struct TraxPacket {
    float kHeading;
    float kPitch;
    float kRoll;
    char kHeadingStatus;
    float KQuaternion[4];
    float kTemperature;
    bool kDistortion;
    bool kCalStatus;
    float kAccelX;
    float kAccelY;
    float kAccelZ;
    float kMagX;
    float kMagY;
    float kMagZ;
    float kGyroX;
    float kGyroY;
    float kGyroZ;
};

TraxPacket parse(std::vector<unsigned char> byte_string);
}// namespace task1

template<>
struct fmt::formatter<task1::TraxPacket> : formatter<std::string> {
    template<typename FormatContext>
    auto format(task1::TraxPacket packet, FormatContext& ctx) {
        return formatter<std::string>::format(
                fmt::format("kHeading: {}\n"
                            "kPitch: {}\n"
                            "kRoll: {}\n"
                            "kHeadingStatus: {}\n"
                            "KQuaternion: [{}, {}, {}, {}]\n"
                            "kTemperature: {}\n"
                            "kDistortion: {}\n"
                            "kCalStatus: {}\n"
                            "kAccelX: {}\n"
                            "kAccelY: {}\n"
                            "kAccelZ: {}\n"
                            "kMagX: {}\n"
                            "kMagY: {}\n"
                            "kMagZ: {}\n"
                            "kGyroX: {}\n"
                            "kGyroY: {}\n"
                            "kGyroZ: {}",
                            packet.kHeading,
                            packet.kPitch,
                            packet.kRoll,
                            packet.kHeadingStatus,
                            packet.KQuaternion[0], packet.KQuaternion[1], packet.KQuaternion[2], packet.KQuaternion[3],
                            packet.kTemperature,
                            packet.kDistortion,
                            packet.kCalStatus,
                            packet.kAccelX,
                            packet.kAccelY,
                            packet.kAccelZ,
                            packet.kMagX,
                            packet.kMagY,
                            packet.kMagZ,
                            packet.kGyroX,
                            packet.kGyroY,
                            packet.kGyroZ),
                ctx);
    }
};
