#ifndef _DPU_CKP_STRUCK_H_
#define _DPU_CKP_STRUCK_H_
#include <string>
#include <cstring>
#define DPU_CKP_DISABLE 0
class tag_base
{
public:
    tag_base(unsigned int id) : m_id(id) {};
    unsigned int m_id{};
    mutable uint64_t m__marker = 0;
    void reset(unsigned char) {}
};

#include "tag.inc.h"


const static char g_hex_map_table[16] = {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
};


void ck_dump(void* ckp);

class buff_c
{
public:
    buff_c();
    ~buff_c();
    static const unsigned int BUF_SIZE = 4096;
    void initial(unsigned int id, std::string file_name, std::string dump_dir = "");
    void close();
    void pushfield(unsigned long long v, unsigned int bits);
    void pushstr(char c);
    unsigned char m_buff[BUF_SIZE]{};
    unsigned int m_offset{};
    unsigned int m_id{};
    FILE* m_fp{};
};



class ckp_c
{
public:
    static ckp_c* inst()
    {
        static ckp_c inst;
        return &inst;
    }
    void initial(bool dump_en, std::string fn, int ckp_id = -1);
    void dump(void* ckp);
    void close(int ckp_id = -1);
private:
    ckp_c();
    ~ckp_c();
#include "func.inc"
    bool m_is_dump{};
    buff_c m_buff[CK_NUM];
};


#endif
