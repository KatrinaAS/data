// Copyright (c) 2019 Katrina Swales
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "data/stream.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "gmock/gmock-matchers.h"
namespace {
class StreamTest : public ::testing::Test {
protected:
    void SetUp() override {
        test= std::vector<data::byte>();
        for(int i=0;i<20;i++)
            test.push_back(i+1);
        sliceTestWrite = data::slice<data::byte>::make(test);
        sliceTestRead = data::bytes_view{test.data(), test.size()};
    }

    void TearDown() override {
    }

    std::vector<data::byte> test;
    data::slice<data::byte> sliceTestWrite;
    data::bytes_view sliceTestRead;
};

    TEST_F(StreamTest, StreamWriteUint16Big) {
        data::writer writer(sliceTestWrite);
        writer = writer << data::ordered<uint16_t, data::big>::as(4096);
        EXPECT_THAT(test, ::testing::ElementsAre(0x10,00,3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
        writer = writer << data::ordered<uint16_t, data::big>::as(9023) ;
        EXPECT_THAT(test, ::testing::ElementsAre(0x10,00,0x23, 0x3F, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
    }

    TEST_F(StreamTest, StreamWriteUint16Little) {
        data::writer writer(sliceTestWrite);
        writer = writer << data::ordered<uint16_t, data::little>::as(4096);
        EXPECT_THAT(test,::testing::ElementsAre(00,0x10,3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
        writer = writer << data::ordered<uint16_t, data::little>::as(9023);
        EXPECT_THAT(test,::testing::ElementsAre(00,0x10,0x3F, 0x23, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
    }

    TEST_F(StreamTest, StreamWriteInt16Big) {
        data::writer writer(sliceTestWrite);
        writer = writer << data::ordered<int16_t, data::big>::as(4096);
        EXPECT_THAT(test,::testing::ElementsAre(0x10,00,3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
        writer = writer << data::ordered<int16_t, data::big>::as(-9023);
        EXPECT_THAT(test,::testing::ElementsAre(0x10,00,0xDC, 0xC1, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
    }

    TEST_F(StreamTest, StreamWriteInt16Little) {
        data::writer writer(sliceTestWrite);
        writer = writer << data::ordered<int16_t, data::little>::as(4096);
        EXPECT_THAT(test,::testing::ElementsAre(00,0x10,3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
        writer = writer << data::ordered<int16_t, data::little>::as(-9023);
        EXPECT_THAT(test,::testing::ElementsAre(00,0x10,0xC1, 0xDC, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
    }

    TEST_F(StreamTest, SliceWriteUint32Big) {
        data::writer writer(sliceTestWrite);
        writer = writer << data::ordered<uint32_t, data::big>::as(2859322050);
        EXPECT_THAT(test,::testing::ElementsAre(0xAA,0x6D,0xCA, 0xC2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
        writer = writer << data::ordered<uint32_t, data::big>::as(2805395218);
        EXPECT_THAT(test,::testing::ElementsAre(0xAA,0x6D,0xCA, 0xC2, 0xA7, 0x36, 0xEF, 0x12, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
    }

    TEST_F(StreamTest, StreamWriteUint32Little) {
        data::writer writer(sliceTestWrite);
        writer = writer << data::ordered<uint32_t, data::little>::as(2859322050);
        EXPECT_THAT(test,::testing::ElementsAre(0xC2,0xCA,0x6D,0xAA , 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
        writer = writer << data::ordered<uint32_t, data::little>::as(2805395218);
        EXPECT_THAT(test,::testing::ElementsAre(0xC2,0xCA,0x6D,0xAA , 0x12, 0xEF, 0x36, 0xA7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
    }

    TEST_F(StreamTest, StreamWriteInt32Big) {
        data::writer writer(sliceTestWrite);
        writer = writer << data::ordered<int32_t, data::big>::as((int32_t)2859322050);
        EXPECT_THAT(test,::testing::ElementsAre(0xAA,0x6D,0xCA, 0xC2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
        writer = writer << data::ordered<int32_t, data::big>::as((int32_t)-280539521);
        EXPECT_THAT(test,::testing::ElementsAre(0xAA,0x6D,0xCA, 0xC2, 0xEF, 0x47, 0x4E, 0x7F, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
    }

    TEST_F(StreamTest, StreamWriteInt32Little) {
        data::writer writer(sliceTestWrite);
        writer = writer << data::ordered<int32_t, data::little>::as((int32_t)2859322050);
        EXPECT_THAT(test,::testing::ElementsAre(0xC2,0xCA,0x6D,0xAA , 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
        writer = writer << data::ordered<int32_t, data::little>::as((int32_t)-280539521);
        EXPECT_THAT(test,::testing::ElementsAre(0xC2,0xCA,0x6D,0xAA , 0x7F, 0x4E, 0x47, 0xEF, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
    }


    TEST_F(StreamTest, StreamWriteUint64Big) {
        data::writer writer(sliceTestWrite);
        writer = writer << data::ordered<uint64_t, data::big>::as(2387559956438732708);
        EXPECT_THAT(test,::testing::ElementsAre(0x21,0x22,0x51, 0x21, 0x6B, 0x7A, 0x4F, 0xA4, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
        writer = writer << data::ordered<uint64_t, data::big>::as(17900722797183299418);
        EXPECT_THAT(test,::testing::ElementsAre(0x21,0x22,0x51, 0x21, 0x6B, 0x7A, 0x4F, 0xA4, 0xF8, 0x6C, 0x24, 0x8A, 0xBC, 0xD8, 0xEF, 0x5A, 17, 18, 19, 20));
        auto o = data::ordered<uint64_t, data::big>::as(17906342797856292348);
        EXPECT_THROW(writer << o, data::end_of_stream);
    }

    TEST_F(StreamTest, StreamWriteUint64Little) {
        data::writer writer(sliceTestWrite);
        writer = writer << data::ordered<uint64_t, data::little>::as(2387559956438732708);
        EXPECT_THAT(test,::testing::ElementsAre(0xA4,0x4F,0x7A, 0x6B, 0x21, 0x51, 0x22, 0x21, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
        writer = writer << data::ordered<uint64_t, data::little>::as(17900722797183299418);
        EXPECT_THAT(test,::testing::ElementsAre(0xA4,0x4F,0x7A, 0x6B, 0x21, 0x51, 0x22, 0x21, 0x5A, 0xEF, 0xD8, 0xBC, 0x8A, 0x24, 0x6C, 0xF8, 17, 18, 19, 20));
        auto o = data::ordered<uint64_t, data::little>::as(17906342797856292348);
        EXPECT_THROW(writer << o, data::end_of_stream);
    }

    TEST_F(StreamTest, StreamWriteInt64Big) {
        data::writer writer(sliceTestWrite);
        writer = writer << data::ordered<int64_t, data::big>::as(2387559956438732708);
        EXPECT_THAT(test,::testing::ElementsAre(0x21,0x22,0x51, 0x21, 0x6B, 0x7A, 0x4F, 0xA4, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
        writer = writer << data::ordered<int64_t, data::big>::as(-1790072279718329941);
        EXPECT_THAT(test,::testing::ElementsAre(0x21,0x22,0x51, 0x21, 0x6B, 0x7A, 0x4F, 0xA4, 0xE7, 0x28, 0x62, 0xBE, 0xED, 0x1D, 0x81, 0xAB, 17, 18, 19, 20));
        auto o = data::ordered<int64_t, data::big>::as(static_cast<long>(17906342797856292348));
        EXPECT_THROW(writer << o, data::end_of_stream);
    }

    TEST_F(StreamTest, StreamWriteInt64Little) {
        data::writer writer(sliceTestWrite);
        writer = writer << data::ordered<int64_t, data::little>::as(2387559956438732708);
        EXPECT_THAT(test,::testing::ElementsAre(0xA4,0x4F,0x7A, 0x6B, 0x21, 0x51, 0x22, 0x21, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
        writer = writer << data::ordered<int64_t, data::little>::as(-1790072279718329941);
        EXPECT_THAT(test,::testing::ElementsAre(0xA4,0x4F,0x7A, 0x6B, 0x21, 0x51, 0x22, 0x21, 0xAB, 0x81, 0x1D, 0xED, 0xBE, 0x62, 0x28, 0xE7, 17, 18, 19, 20));
        auto o = data::ordered<int64_t, data::little>::as(static_cast<long>(17906342797856292348));
        EXPECT_THROW(writer << o, data::end_of_stream);
    }

    TEST_F(StreamTest, StreamWriteBytes) {
        data::writer writer(sliceTestWrite);
        data::bytes enter{0xab,0xcd,0xef,0x01};
        writer << enter;
        EXPECT_THAT(test,::testing::ElementsAre(0xab,0xcd,0xef,0x01, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
    }


    TEST_F(StreamTest, StreamReadUint16Big) {
        data::reader reader(sliceTestRead);
        data::ordered<uint16_t, data::big> testUint;
        reader >> testUint;
        EXPECT_EQ(testUint, 0x102);
        reader >> testUint;
        EXPECT_EQ(testUint, 0x304);
    }

    TEST_F(StreamTest, StreamReadUint16Little) {
        data::reader reader(sliceTestRead);
        data::ordered<uint16_t, data::little> testUint;
        reader >> testUint;
        EXPECT_EQ(testUint, 513);
        reader >> testUint;
        EXPECT_EQ(testUint, 1027);
    }

    TEST_F(StreamTest, StreamReadInt16Big) {
        data::reader reader(sliceTestRead);
        data::ordered<int16_t, data::big> testUint;
        reader >> testUint;
        EXPECT_EQ(testUint, 258);
        reader >> testUint;
        EXPECT_EQ(testUint, 772);
    }

    TEST_F(StreamTest, StreamReadInt16Little) {
        data::reader reader(sliceTestRead);
        data::ordered<int16_t, data::little> testUint;
        reader >> testUint;
        EXPECT_EQ(testUint,513);
        reader >> testUint;
        EXPECT_EQ(testUint,1027);
    }

    TEST_F(StreamTest, StreamReadUint32Big) {
        data::reader reader(sliceTestRead);
        data::ordered<uint32_t, data::big> testUint;
        reader >> testUint;
        EXPECT_EQ(testUint, 16909060);
        reader >> testUint;
        EXPECT_EQ(testUint, 84281096);
    }

    TEST_F(StreamTest, StreamReadUint32Little) {
        data::reader reader(sliceTestRead);
        data::ordered<uint32_t, data::little> testUint;
        reader >> testUint;
        EXPECT_EQ(testUint, 67305985);
        reader >> testUint;
        EXPECT_EQ(testUint, 134678021);
    }


    TEST_F(StreamTest, StreamReadInt32Big) {
        data::reader reader(sliceTestRead);
        data::ordered<int32_t, data::big> testUint;
        reader >> testUint;
        EXPECT_EQ(testUint, 16909060);
        reader >> testUint;
        EXPECT_EQ(testUint, 84281096);
    }

    TEST_F(StreamTest, StreamReadInt32Little) {
        data::reader reader(sliceTestRead);
        data::ordered<uint32_t, data::little> testUint;
        reader >> testUint;
        EXPECT_EQ(testUint, 67305985);
        reader >> testUint;
        EXPECT_EQ(testUint, 134678021);
    }

    TEST_F(StreamTest, StreamReadUint64Big) {
        data::reader reader(sliceTestRead);
        data::ordered<uint64_t, data::big> testUint;
        reader >> testUint;
        EXPECT_EQ(testUint, 72623859790382856);
        reader >> testUint;
        EXPECT_EQ(testUint, 651345242494996240);
        EXPECT_THROW(reader >> testUint,data::end_of_stream);

    }

    TEST_F(StreamTest, StreamReadUint64Little) {
        data::reader reader(sliceTestRead);
        data::ordered<uint64_t, data::little> testUint;
        reader >> testUint;
        EXPECT_EQ(testUint, 578437695752307201);
        reader >> testUint;
        EXPECT_EQ(testUint, 1157159078456920585);
        EXPECT_THROW(reader >> testUint,data::end_of_stream);
    }

    TEST_F(StreamTest, StreamReadInt64Big) {
        data::reader reader(sliceTestRead);
        data::ordered<int64_t, data::big> testUint;
        reader >> testUint;
        EXPECT_EQ(testUint, 72623859790382856);
        reader >> testUint;
        EXPECT_EQ(testUint, 651345242494996240);
        EXPECT_THROW(reader >> testUint, data::end_of_stream);

    }

    TEST_F(StreamTest, StreamReadInt64Little) {
        data::reader reader(sliceTestRead);
        data::ordered<int64_t, data::little>  testUint;
        reader >> testUint;
        EXPECT_EQ(testUint, 578437695752307201);
        reader >> testUint;
        EXPECT_EQ(testUint, 1157159078456920585);
        EXPECT_THROW(reader >> testUint, data::end_of_stream);
    }

    TEST_F(StreamTest, StreamReadBytes) {
        data::reader reader(sliceTestRead);
        std::vector<data::byte> testUint(4);
        reader >> testUint;
        EXPECT_THAT(testUint,::testing::ElementsAre(01,02,03,04));
    }

    TEST_F(StreamTest, StreamGetPositiveRange) {
        EXPECT_THAT(sliceTestWrite.range(2,5),::testing::ElementsAre(3,4,5));
        EXPECT_THAT(sliceTestWrite.range(0,5),::testing::ElementsAre(1,2,3,4,5));
        EXPECT_THAT(sliceTestWrite.range(15,19),::testing::ElementsAre(16,17,18,19));
        EXPECT_THAT(sliceTestWrite.range(15,20),::testing::ElementsAre(16,17,18,19,20));
        EXPECT_THAT(sliceTestWrite.range(0,22),::testing::ElementsAre());
    }
    TEST_F(StreamTest, StreamReadUpToNegative) {
        EXPECT_THAT(sliceTestWrite.range(0,-4),::testing::ElementsAre(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16));
        EXPECT_THAT(sliceTestWrite.range(5,-12),::testing::ElementsAre(6,7,8));

    }

    TEST_F(StreamTest, StreamReadNegativeToEnd) {
        EXPECT_THAT(sliceTestWrite.range(-4),::testing::ElementsAre(17,18,19,20));
        EXPECT_THAT(sliceTestWrite.range(-20),::testing::ElementsAre(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20));
    }
}
