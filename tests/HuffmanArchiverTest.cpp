#include "HuffmanArchiverTest.hpp"

static const int32_t SIZE = 1 << BYTE;

void HuffmanArchiverTest::testIOSource_SMALL_SIZE_TEXT() {
    HuffmanArchiver archiver;
    std::string file_in = "test.txt";
    std::vector <uint8_t> ideal {0, 1, 2, 3};
    archiver.output_decoded(file_in, ideal);
    std::vector <uint8_t> source;
    archiver.input_source(file_in, source);
    DO_CHECK(source == ideal);
    remove("test.txt");
}

void HuffmanArchiverTest::testIOSource_BIG_SIZE_TEXT() {
    HuffmanArchiver archiver;
    std::string file_in = "test.txt";
    std::vector <uint8_t> ideal(1 << 20);
    for (std::size_t i = 0; i < ideal.size(); ++i) {
        ideal[i] = i % SIZE;
    }
    archiver.output_decoded(file_in, ideal);
    std::vector <uint8_t> source;
    archiver.input_source(file_in, source);
    DO_CHECK(source == ideal);
    remove("test.txt");
}

void HuffmanArchiverTest::testIOSource_SMALL_SIZE_BIN() {
    HuffmanArchiver archiver;
    std::string file_in = "test.bin";
    std::vector <uint8_t> ideal {0, 1, 2, 3};
    archiver.output_decoded(file_in, ideal);
    std::vector <uint8_t> source;
    archiver.input_source(file_in, source);
    DO_CHECK(source == ideal);
    remove("test.bin");
}

void HuffmanArchiverTest::testIOSource_BIG_SIZE_BIN() {
    HuffmanArchiver archiver;
    std::string file_in = "test.bin";
    std::vector <uint8_t> ideal(1 << 20);
    for (std::size_t i = 0; i < ideal.size(); ++i) {
        ideal[i] = i % SIZE;
    }
    archiver.output_decoded(file_in, ideal);
    std::vector <uint8_t> source;
    archiver.input_source(file_in, source);
    DO_CHECK(source == ideal);
    remove("test.bin");
}

void HuffmanArchiverTest::testIOEncoded_SMALL_SIZE_TEXT() {
    HuffmanArchiver archiver;
    std::string file_out = "test.txt";
    std::vector <bool> encoded_ideal {0, 1, 0, 1, 1, 1, 0, 0, 1};
    std::vector <int32_t> cnt_ideal(SIZE);
    for (std::size_t i = 0; i < BYTE; ++i) {
        cnt_ideal[i] = i * i + 1;
    }
    archiver.output_encoded(file_out, encoded_ideal, cnt_ideal);
    std::vector <bool> encoded;
    std::vector <int32_t> cnt(SIZE);
    archiver.input_encoded(file_out, encoded, cnt);
    DO_CHECK(encoded == encoded_ideal && cnt == cnt_ideal);
    remove("test.txt");
}

void HuffmanArchiverTest::testIOEncoded_BIG_SIZE_TEXT() {
    HuffmanArchiver archiver;
    std::string file_out = "test.txt";
    std::vector <bool> encoded_ideal((1 << 20) + 3);
    for (std::size_t i = 0; i < encoded_ideal.size(); ++i) {
        encoded_ideal[i] = (i % 3) % 2;
    }
    std::vector <int32_t> cnt_ideal(SIZE);
    for (int32_t i = 0; i < SIZE - 1; ++i) {
        cnt_ideal[i] = i + 1;
    }
    archiver.output_encoded(file_out, encoded_ideal, cnt_ideal);
    std::vector <bool> encoded;
    std::vector <int32_t> cnt(SIZE);
    archiver.input_encoded(file_out, encoded, cnt);
    DO_CHECK(encoded == encoded_ideal && cnt == cnt_ideal);
    remove("test.txt");
}

void HuffmanArchiverTest::testIOEncoded_SMALL_SIZE_BIN() {
    HuffmanArchiver archiver;
    std::string file_out = "test.bin";
    std::vector <bool> encoded_ideal {0, 1, 0, 1, 1, 1, 0, 0, 1};
    std::vector <int32_t> cnt_ideal(SIZE);
    for (std::size_t i = 0; i < BYTE; ++i) {
        cnt_ideal[i] = i * i + 1;
    }
    archiver.output_encoded(file_out, encoded_ideal, cnt_ideal);
    std::vector <bool> encoded;
    std::vector <int32_t> cnt(SIZE);
    archiver.input_encoded(file_out, encoded, cnt);
    DO_CHECK(encoded == encoded_ideal && cnt == cnt_ideal);
    remove("test.bin");
}

void HuffmanArchiverTest::testIOEncoded_BIG_SIZE_BIN() {
    HuffmanArchiver archiver;
    std::string file_out = "test.bin";
    std::vector <bool> encoded_ideal((1 << 20) + 3);
    for (std::size_t i = 0; i < encoded_ideal.size(); ++i) {
        encoded_ideal[i] = (i % 3) % 2;
    }
    std::vector <int32_t> cnt_ideal(SIZE);
    for (int32_t i = 0; i < SIZE - 1; ++i) {
        cnt_ideal[i] = i + 1;
    }
    archiver.output_encoded(file_out, encoded_ideal, cnt_ideal);
    std::vector <bool> encoded;
    std::vector <int32_t> cnt(SIZE);
    archiver.input_encoded(file_out, encoded, cnt);
    DO_CHECK(encoded == encoded_ideal && cnt == cnt_ideal);
    remove("test.bin");
}

void HuffmanArchiverTest::testIOSource_EMPTY_TEXT() {
    HuffmanArchiver archiver;
    std::string file_in = "test.txt";
    std::vector <uint8_t> ideal;
    archiver.output_decoded(file_in, ideal);
    std::vector <uint8_t> source;
    archiver.input_source(file_in, source);
    DO_CHECK(source == ideal);
    remove("test.txt");
}

void HuffmanArchiverTest::testIOSource_EMPTY_BIN() {
    HuffmanArchiver archiver;
    std::string file_in = "test.bin";
    std::vector <uint8_t> ideal;
    archiver.output_decoded(file_in, ideal);
    std::vector <uint8_t> source;
    archiver.input_source(file_in, source);
    DO_CHECK(source == ideal);
    remove("test.bin");
}

void HuffmanArchiverTest::testIOEncoded_EMPTY_TEXT() {
    HuffmanArchiver archiver;
    std::string file_out = "test.txt";
    std::vector <bool> encoded_ideal;
    std::vector <int32_t> cnt_ideal(SIZE);
    archiver.output_encoded(file_out, encoded_ideal, cnt_ideal);
    std::vector <bool> encoded;
    std::vector <int32_t> cnt(SIZE);
    archiver.input_encoded(file_out, encoded, cnt);
    DO_CHECK(encoded == encoded_ideal && cnt == cnt_ideal);
    remove("test.txt");
}

void HuffmanArchiverTest::testIOEncoded_EMPTY_BIN() {
    HuffmanArchiver archiver;
    std::string file_out = "test.bin";
    std::vector <bool> encoded_ideal;
    std::vector <int32_t> cnt_ideal(SIZE);
    archiver.output_encoded(file_out, encoded_ideal, cnt_ideal);
    std::vector <bool> encoded;
    std::vector <int32_t> cnt(SIZE);
    archiver.input_encoded(file_out, encoded, cnt);
    DO_CHECK(encoded == encoded_ideal && cnt == cnt_ideal);
    remove("test.txt");
}


void HuffmanArchiverTest::testCounting_EMPTY() {
    HuffmanArchiver archiver;
    std::vector <uint8_t> source;
    std::vector <int32_t> cnt(SIZE);
    archiver.counting(source, cnt);
    DO_CHECK(cnt == std::vector <int32_t> (SIZE));
}

void HuffmanArchiverTest::testCounting_ONE_CHAR() {
    HuffmanArchiver archiver;
    std::vector <uint8_t> source {'X'};
    std::vector <int32_t> cnt(SIZE);
    archiver.counting(source, cnt);
    std::vector <int32_t> cnt_ideal(SIZE);
    cnt_ideal['X'] = 1;
    DO_CHECK(cnt == cnt_ideal);
}

void HuffmanArchiverTest::testCounting_EVEN() {
    HuffmanArchiver archiver;
    std::vector <uint8_t> source;
    std::vector <int32_t> cnt(SIZE);
    for (std::size_t i = 1; i < cnt.size(); i += 2) {
        source.push_back(i);
    }
    archiver.counting(source, cnt);
    std::vector <int32_t> cnt_ideal(SIZE);
    for (std::size_t i = 0; i < cnt_ideal.size(); ++i) {
        cnt_ideal[i] = i % 2;
    }
    DO_CHECK(cnt == cnt_ideal);
}

void HuffmanArchiverTest::testCounting_FULL() {
    HuffmanArchiver archiver;
    std::vector <uint8_t> source;
    std::vector <int32_t> cnt(SIZE);
    for (std::size_t i = 0; i < cnt.size() * BYTE; ++i) {
        source.push_back(i % cnt.size());
    }
    archiver.counting(source, cnt);
    std::vector <int32_t> cnt_ideal(SIZE);
    for (std::size_t i = 0; i < cnt_ideal.size(); ++i) {
        cnt_ideal[i] = BYTE;
    }
    DO_CHECK(cnt == cnt_ideal);
}


void HuffmanArchiverTest::testEncodeDecode_EMPTY_TEXT() {
    HuffmanArchiver archiver;
    std::string file_in = "empty.txt";
    std::string file_out = "zip.txt";
    std::vector <uint8_t> res;
    archiver.output_decoded(file_in, res);
    archiver.encode(file_in, file_out);
    archiver.decode(file_out, file_in);
    archiver.input_source(file_in, res);
    DO_CHECK(res == std::vector <uint8_t> ());
    remove("empty.txt");
    remove("zip.txt");
}

void HuffmanArchiverTest::testEncodeDecode_EMPTY_BIN() {
    HuffmanArchiver archiver;
    std::string file_in = "empty.bin";
    std::string file_out = "zip.bin";
    std::vector <uint8_t> res;
    archiver.output_decoded(file_in, res);
    archiver.encode(file_in, file_out);
    archiver.decode(file_out, file_in);
    archiver.input_source(file_in, res);
    DO_CHECK(res == std::vector <uint8_t> ());
    remove("empty.bin");
    remove("zip.bin");
}

void HuffmanArchiverTest::testEncodeDecode_SMALL_SIZE() {
    HuffmanArchiver archiver;
    std::string file_in = "test.bin";
    std::string file_out = "zip.txt";
    std::vector <uint8_t> res_ideal(BYTE + 1);
    for (std::size_t i = 0; i < res_ideal.size(); ++i) {
        res_ideal[i] = i % 3 + 1;
    }
    archiver.output_decoded(file_in, res_ideal);
    archiver.encode(file_in, file_out);
    archiver.decode(file_out, file_in);
    std::vector <uint8_t> res;
    archiver.input_source(file_in, res);
    DO_CHECK(res == res_ideal);
    remove("test.bin");
    remove("zip.txt");
}

void HuffmanArchiverTest::testEncodeDecode_BIG_SIZE() {
    HuffmanArchiver archiver;
    std::string file_in = "test.txt";
    std::string file_out = "zip.bin";
    std::vector <uint8_t> res_ideal((1 << 20) + 2);
    for (std::size_t i = 0; i < res_ideal.size(); ++i) {
        res_ideal[i] = i % SIZE;
    }
    archiver.output_decoded(file_in, res_ideal);
    archiver.encode(file_in, file_out);
    archiver.decode(file_out, file_in);
    std::vector <uint8_t> res;
    archiver.input_source(file_in, res);
    DO_CHECK(res == res_ideal);
    remove("test.txt");
    remove("zip.bin");
}


void HuffmanArchiverTest::testIOSource_NO_FILE() {
    HuffmanArchiver archiver;
    std::string file_in = "no_file.txt";
    bool res = false;
    try {
        std::vector <uint8_t> source;
        archiver.input_source(file_in, source);
    }
    catch (HuffmanException & h) {
        res = (std::string(h.what()) == "Unable to open file.");
    }
    DO_CHECK(res);
}

void HuffmanArchiverTest::testIOEncoded_NO_FILE() {
    HuffmanArchiver archiver;
    std::string file_in = "no_file.txt";
    bool res = false;
    try {
        std::vector <bool> encoded;
        std::vector <int32_t> cnt(SIZE);
        archiver.input_encoded(file_in, encoded, cnt);
    }
    catch (HuffmanException & h) {
        res = (std::string(h.what()) == "Unable to open file.");
    }
    DO_CHECK(res);
}

void HuffmanArchiverTest::testIOEncoded_EOF() {
    HuffmanArchiver archiver;
    std::string file_in = "test.txt";
    bool res = false;
    try {
        std::vector <uint8_t> source {1, 0};
        archiver.output_decoded(file_in, source);
        std::vector <bool> encoded;
        std::vector <int32_t> cnt(1 << BYTE);
        archiver.input_encoded(file_in, encoded, cnt);
    }
    catch (HuffmanException & h) {
        res = (std::string(h.what()) == "Invalid format.");
    }
    DO_CHECK(res);
    remove("test.txt");
}

void HuffmanArchiverTest::testEncodeDecode_INVALID_FILE() {
    HuffmanArchiver archiver;
    std::string file_in = "test.txt";
    bool res = false;
    try {
        std::vector <uint8_t> source {1, 0};
        archiver.output_decoded(file_in, source);
        std::vector <bool> encoded;
        std::vector <int32_t> cnt(1 << BYTE);
        archiver.input_encoded(file_in, encoded, cnt);
    }
    catch (HuffmanException & h) {
        res = (std::string(h.what()) == "Invalid format.");
    }
    DO_CHECK(res);
    remove("test.txt");
}


void HuffmanArchiverTest::runAllTests() {
    testIOSource_SMALL_SIZE_TEXT();
    testIOSource_BIG_SIZE_TEXT();
    testIOSource_SMALL_SIZE_BIN();
    testIOSource_BIG_SIZE_BIN();

    testIOEncoded_SMALL_SIZE_TEXT();
    testIOEncoded_BIG_SIZE_TEXT();
    testIOEncoded_SMALL_SIZE_BIN();
    testIOEncoded_BIG_SIZE_BIN();

    testIOSource_EMPTY_TEXT();
    testIOSource_EMPTY_BIN();
    testIOEncoded_EMPTY_TEXT();
    testIOEncoded_EMPTY_BIN();

    testCounting_EMPTY();
    testCounting_ONE_CHAR();
    testCounting_EVEN();
    testCounting_FULL();

    testEncodeDecode_EMPTY_TEXT();
    testEncodeDecode_EMPTY_BIN();
    testEncodeDecode_SMALL_SIZE();
    testEncodeDecode_BIG_SIZE();

    testIOSource_NO_FILE();
    testIOEncoded_NO_FILE();
    testIOEncoded_EOF();
    testEncodeDecode_INVALID_FILE();
}
