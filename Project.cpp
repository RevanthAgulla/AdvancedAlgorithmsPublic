#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdint> 
#include <cstring>

// This class implements the SHA-256 hashing algorithm, which is the foundation of blockchain consensus.
class SHA256
{
public:
    SHA256();
    void update(const unsigned char *data, size_t len);
    void final(unsigned char hash[32]);

private:
    void transform(const unsigned char data[]);

    uint32_t m_state[8];      // Hash state (a-h)
    unsigned char m_data[64]; // Data block being processed
    uint32_t m_datalen;       // Current length of data in m_data
    uint64_t m_bitlen;        // Total length of message in bits

    // The round constants (first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311)
    static const uint32_t k[64];
};

// Macro for right rotation
#define ROTRIGHT(a, b) (((a) >> (b)) | ((a) << (32 - (b))))

// SHA-256 round constants
const uint32_t SHA256::k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

// ----------------------------------------------------------------------------
// Constructor: Initialize hash values (first 32 bits of the fractional parts
// of the square roots of the first 8 primes 2..19)
SHA256::SHA256() : m_datalen(0), m_bitlen(0)
{
    m_state[0] = 0x6a09e667;
    m_state[1] = 0xbb67ae85;
    m_state[2] = 0x3c6ef372;
    m_state[3] = 0xa54ff53a;
    m_state[4] = 0x510e527f;
    m_state[5] = 0x9b05688c;
    m_state[6] = 0x1f83d9ab;
    m_state[7] = 0x5be0cd19;
}

// ----------------------------------------------------------------------------
// transform: Process one 512-bit block of the message. This is the heart of our consensus mechanism where each block is mixed thoroughly using rotations, shifts, and modular additions.
void SHA256::transform(const unsigned char data[])
{
    uint32_t w[64];
    uint32_t a, b, c, d, e, f, g, h;

    // Prepare the message schedule 'w'
    for (uint32_t i = 0; i < 16; ++i)
    {
        w[i] = (data[i * 4] << 24);
        w[i] |= (data[i * 4 + 1] << 16);
        w[i] |= (data[i * 4 + 2] << 8);
        w[i] |= (data[i * 4 + 3]);
    }
    for (uint32_t i = 16; i < 64; ++i)
    {
        uint32_t s0 = ROTRIGHT(w[i - 15], 7) ^ ROTRIGHT(w[i - 15], 18) ^ (w[i - 15] >> 3);
        uint32_t s1 = ROTRIGHT(w[i - 2], 17) ^ ROTRIGHT(w[i - 2], 19) ^ (w[i - 2] >> 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }

    // Initialize working variables with current hash state
    a = m_state[0];
    b = m_state[1];
    c = m_state[2];
    d = m_state[3];
    e = m_state[4];
    f = m_state[5];
    g = m_state[6];
    h = m_state[7];

    // Main compression loop: each iteration is like reaching consensus on one sub-block.
    for (uint32_t i = 0; i < 64; ++i)
    {
        uint32_t S1 = ROTRIGHT(e, 6) ^ ROTRIGHT(e, 11) ^ ROTRIGHT(e, 25);
        uint32_t ch = (e & f) ^ ((~e) & g);
        uint32_t temp1 = h + S1 + ch + k[i] + w[i];
        uint32_t S0 = ROTRIGHT(a, 2) ^ ROTRIGHT(a, 13) ^ ROTRIGHT(a, 22);
        uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
        uint32_t temp2 = S0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    // Add the compressed block to the current hash state (consensus update)
    m_state[0] += a;
    m_state[1] += b;
    m_state[2] += c;
    m_state[3] += d;
    m_state[4] += e;
    m_state[5] += f;
    m_state[6] += g;
    m_state[7] += h;
}

// ----------------------------------------------------------------------------
// Feed data into the SHA-256 engine. In a blockchain, validators continuously incorporate new transactions
void SHA256::update(const unsigned char *data, size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        m_data[m_datalen] = data[i];
        m_datalen++;
        if (m_datalen == 64)
        {
            transform(m_data);
            m_bitlen += 512;
            m_datalen = 0;
        }
    }
}

// ----------------------------------------------------------------------------
// Complete the hashing process by adding padding and the length. The pre-processing steps mimic how blockchain data is padded and then
// processed in discrete blocks to achieve immutability.
void SHA256::final(unsigned char hash[32])
{
    uint32_t i = m_datalen;

    // Append the '1' bit (0x80 in hex)
    m_data[i++] = 0x80;

    // Pad with zeros until the length in bytes mod 64 equals 56
    if (i > 56)
    {
        while (i < 64)
        {
            m_data[i++] = 0x00;
        }
        transform(m_data);
        i = 0;
    }
    while (i < 56)
    {
        m_data[i++] = 0x00;
    }

    // Append the total message length in bits as a 64-bit big-endian integer
    m_bitlen += m_datalen * 8;
    m_data[63] = m_bitlen;
    m_data[62] = m_bitlen >> 8;
    m_data[61] = m_bitlen >> 16;
    m_data[60] = m_bitlen >> 24;
    m_data[59] = m_bitlen >> 32;
    m_data[58] = m_bitlen >> 40;
    m_data[57] = m_bitlen >> 48;
    m_data[56] = m_bitlen >> 56;
    transform(m_data);

    // Produce the final hash (big-endian format)
    for (i = 0; i < 4; ++i)
    {
        hash[i] = (m_state[0] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 4] = (m_state[1] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 8] = (m_state[2] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 12] = (m_state[3] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 16] = (m_state[4] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 20] = (m_state[5] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 24] = (m_state[6] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 28] = (m_state[7] >> (24 - i * 8)) & 0x000000ff;
    }
}

// ----------------------------------------------------------------------------
//  Reads an input file and computes its SHA-256 hash. This simulates processing a large ledger of transactions in a decentralized blockchain.
int main(int argc, char *argv[])
{
    std::cout << "--------------------------------------------------\n";
    std::cout << " Blockchain Consensus Hash Generator - SHA256\n";
    std::cout << "--------------------------------------------------\n";

    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    // Read the entire file into a string
    std::ifstream file(argv[1], std::ios::binary);
    if (!file)
    {
        std::cerr << "Error: Could not open file '" << argv[1] << "'\n";
        return 1;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string input = buffer.str();

    // Initialize SHA256 engine and process the input
    SHA256 sha256;
    sha256.update(reinterpret_cast<const unsigned char *>(input.c_str()), input.size());
    unsigned char hash[32];
    sha256.final(hash);

    // Output the final hash in hexadecimal format
    std::cout << "SHA-256 Hash:\n";
    for (int i = 0; i < 32; i++)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    std::cout << "\n\nConsensus reached: This is the unique digital fingerprint of your data.\n";
    return 0;
}