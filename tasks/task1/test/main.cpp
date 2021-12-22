#include <gtest/gtest.h>

#include "task1/trax_packet.hpp"

TEST(TraxPacket, test1) {
    std::vector<unsigned char> input;
    input.push_back(0x05);
    input.push_back(0x3F);
    input.push_back(0x80);
    input.push_back(0x00);
    input.push_back(0x00);
    input.push_back(0x09);
    input.push_back(0x01);
    input.push_back(0x1C);
    input.push_back(0x40);
    input.push_back(0x00);
    input.push_back(0x00);
    input.push_back(0x00);
    task1::TraxPacket packet = task1::parse(std::move(input));
    std::cout << fmt::format("{}", packet) << std::endl;
    EXPECT_FLOAT_EQ(packet.kHeading, 1.f);
    EXPECT_EQ(packet.kCalStatus, true);
    EXPECT_FLOAT_EQ(packet.kMagY, 2.f);
}

TEST(TraxPacket, test2) {
    std::vector<unsigned char> input;
    input.push_back(0x4C);
    input.push_back(0x41);
    input.push_back(0xA4);
    input.push_back(0x00);
    input.push_back(0x00);
    input.push_back(0x4B);
    input.push_back(0x3F);
    input.push_back(0x91);
    input.push_back(0xBC);
    input.push_back(0xD8);
    task1::TraxPacket packet = task1::parse(std::move(input));
    std::cout << fmt::format("{}", packet) << std::endl;
    EXPECT_FLOAT_EQ(packet.kGyroY, 1.1385756f);
    EXPECT_FLOAT_EQ(packet.kGyroZ, 20.5f);
}

TEST(TraxPacket, test3) {
    std::vector<unsigned char> input;
    input.push_back(0x07);
    input.push_back(0x41);
    input.push_back(0xA4);
    input.push_back(0x00);
    input.push_back(0x00);
    input.push_back(0x05);
    input.push_back(0x3F);
    input.push_back(0x91);
    input.push_back(0xBC);
    input.push_back(0xD8);
    input.push_back(0x19);
    input.push_back(0x41);
    input.push_back(0x35);
    input.push_back(0x47);
    input.push_back(0xAE);
    task1::TraxPacket packet = task1::parse(std::move(input));
    std::cout << fmt::format("{}", packet) << std::endl;
    EXPECT_FLOAT_EQ(packet.kHeading, 1.1385756f);
    EXPECT_FLOAT_EQ(packet.kRoll, 11.33f);
    EXPECT_FLOAT_EQ(packet.kTemperature, 20.5f);
}

TEST(TraxPacket, test4) {
    std::vector<unsigned char> input;
    input.push_back(0x05);
    input.push_back(0x43);
    input.push_back(0x0D);
    input.push_back(0x08);
    input.push_back(0x3B);
    input.push_back(0x18);
    input.push_back(0x3F);
    input.push_back(0x91);
    input.push_back(0xBC);
    input.push_back(0xD8);
    input.push_back(0x19);
    input.push_back(0x3E);
    input.push_back(0xDF);
    input.push_back(0x4D);
    input.push_back(0xE9);
    input.push_back(0x4D);
    input.push_back(0x42);
    input.push_back(0x28);
    input.push_back(0x69);
    input.push_back(0xE2);
    input.push_back(0x41);
    input.push_back(0xF8);
    input.push_back(0xF5);
    input.push_back(0xC3);
    input.push_back(0x41);
    input.push_back(0xDE);
    input.push_back(0xC2);
    input.push_back(0x8F);
    input.push_back(0x3C);
    input.push_back(0x59);
    input.push_back(0x4D);
    input.push_back(0x0E);
    task1::TraxPacket packet = task1::parse(std::move(input));
    std::cout << fmt::format("{}", packet) << std::endl;
    EXPECT_FLOAT_EQ(packet.kHeading, 141.03215f);
    EXPECT_FLOAT_EQ(packet.kPitch, 1.1385756f);
    EXPECT_FLOAT_EQ(packet.kRoll, 0.43614128f);
    EXPECT_FLOAT_EQ(packet.KQuaternion[0], 42.1034f);
    EXPECT_FLOAT_EQ(packet.KQuaternion[1], 31.12f);
    EXPECT_FLOAT_EQ(packet.KQuaternion[2], 27.845f);
    EXPECT_FLOAT_EQ(packet.KQuaternion[3], 0.013263f);
}

TEST(TraxPacket, test5) {
    std::vector<unsigned char> input;
    input.push_back(0x05);
    input.push_back(0x43);
    input.push_back(0x0D);
    input.push_back(0x08);
    input.push_back(0x3B);
    input.push_back(0x18);
    input.push_back(0x3F);
    input.push_back(0x91);
    input.push_back(0xBC);
    input.push_back(0xD8);
    input.push_back(0x19);
    input.push_back(0x3E);
    input.push_back(0xDF);
    input.push_back(0x4D);
    input.push_back(0xE9);
    input.push_back(0x4F);
    input.push_back(0x00);
    input.push_back(0x08);
    input.push_back(0x00);
    input.push_back(0x15);
    input.push_back(0xBC);
    input.push_back(0xA4);
    input.push_back(0x08);
    input.push_back(0xC0);
    input.push_back(0x16);
    input.push_back(0x3B);
    input.push_back(0xFB);
    input.push_back(0x4D);
    input.push_back(0xAB);
    input.push_back(0x17);
    input.push_back(0x3F);
    input.push_back(0x80);
    input.push_back(0xF5);
    input.push_back(0x08);
    input.push_back(0x1B);
    input.push_back(0xC1);
    input.push_back(0x6E);
    input.push_back(0xA4);
    input.push_back(0x37);
    input.push_back(0x1C);
    input.push_back(0xC1);
    input.push_back(0x2D);
    input.push_back(0x31);
    input.push_back(0x27);
    input.push_back(0x1D);
    input.push_back(0x42);
    input.push_back(0x51);
    input.push_back(0x3D);
    input.push_back(0x4F);
    input.push_back(0x4A);
    input.push_back(0x00);
    input.push_back(0x00);
    input.push_back(0x00);
    input.push_back(0x00);
    input.push_back(0x4B);
    input.push_back(0x00);
    input.push_back(0x00);
    input.push_back(0x00);
    input.push_back(0x00);
    input.push_back(0x4C);
    input.push_back(0x00);
    input.push_back(0x00);
    input.push_back(0x00);
    input.push_back(0x00);
    task1::TraxPacket packet = task1::parse(std::move(input));
    std::cout << fmt::format("{}", packet) << std::endl;
    EXPECT_FLOAT_EQ(packet.kHeading, 141.03215f);
    EXPECT_FLOAT_EQ(packet.kPitch, 1.1385756f);
    EXPECT_FLOAT_EQ(packet.kRoll, 0.43614128f);
    EXPECT_EQ(packet.kHeadingStatus, 0);
    EXPECT_EQ(packet.kDistortion, false);
    EXPECT_FLOAT_EQ(packet.kAccelX, -0.0200237f);
    EXPECT_FLOAT_EQ(packet.kAccelY, 0.00766917f);
    EXPECT_FLOAT_EQ(packet.kAccelZ, 1.0074778f);
    EXPECT_FLOAT_EQ(packet.kMagX, -14.915092f);
    EXPECT_FLOAT_EQ(packet.kMagY, -10.8245f);
    EXPECT_FLOAT_EQ(packet.kMagZ, 52.309872f);
    EXPECT_FLOAT_EQ(packet.kGyroX, 0.f);
    EXPECT_FLOAT_EQ(packet.kGyroY, 0.f);
    EXPECT_FLOAT_EQ(packet.kGyroZ, 0.f);
}
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
