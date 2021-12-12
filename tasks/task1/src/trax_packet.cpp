#include "task1/trax_packet.hpp"
#include <cstring>

namespace task1 {
namespace {
void reorder(std::vector<unsigned char>::iterator begin, std::vector<unsigned char>::iterator end) {
    if (std::distance(begin, end) < 4) {
        return;
    }
    for (auto it = begin; it != end; std::advance(it, 4)) {
        std::string reordered{std::reverse_iterator{it + 4}, std::reverse_iterator{it}};
        std::copy(reordered.begin(), reordered.end(), it);
    }
}

template<typename T>
std::vector<unsigned char>::iterator parse_impl(std::vector<unsigned char>::iterator it, T& data) {
    auto end = it + sizeof(T);
    reorder(it, end);
    std::memcpy(&data, it.base(), sizeof(T));
    return end;
}
}// namespace

TraxPacket parse(std::vector<unsigned char> byte_string) {
    TraxPacket trax_packet{};

    for (auto it = byte_string.begin(); it != byte_string.end();) {
        auto trax_id = static_cast<TraxId>(*it++);
        switch (trax_id) {
            case TraxId::HEADING:
                it = parse_impl(it, trax_packet.kHeading);
                break;
            case TraxId::PITCH:
                it = parse_impl(it, trax_packet.kPitch);
                break;
            case TraxId::ROLL:
                it = parse_impl(it, trax_packet.kRoll);
                break;
            case TraxId::HEADING_STATUS:
                it = parse_impl(it, trax_packet.kHeadingStatus);
                break;
            case TraxId::QUATERNION:
                it = parse_impl(it, trax_packet.KQuaternion);
                break;
            case TraxId::TEMPERATURE:
                it = parse_impl(it, trax_packet.kTemperature);
                break;
            case TraxId::DISTORTION:
                it = parse_impl(it, trax_packet.kDistortion);
                break;
            case TraxId::CAL_STATUS:
                it = parse_impl(it, trax_packet.kCalStatus);
                break;
            case TraxId::ACCEL_X:
                it = parse_impl(it, trax_packet.kAccelX);
                break;
            case TraxId::ACCEL_Y:
                it = parse_impl(it, trax_packet.kAccelY);
                break;
            case TraxId::ACCEL_Z:
                it = parse_impl(it, trax_packet.kAccelZ);
                break;
            case TraxId::MAG_X:
                it = parse_impl(it, trax_packet.kMagX);
                break;
            case TraxId::MAG_Y:
                it = parse_impl(it, trax_packet.kMagY);
                break;
            case TraxId::MAG_Z:
                it = parse_impl(it, trax_packet.kMagZ);
                break;
            case TraxId::GYRO_X:
                it = parse_impl(it, trax_packet.kGyroX);
                break;
            case TraxId::GYRO_Y:
                it = parse_impl(it, trax_packet.kGyroY);
                break;
            case TraxId::GYRO_Z:
                it = parse_impl(it, trax_packet.kGyroZ);
                break;
        }
    }

    return trax_packet;
}
}// namespace task1
