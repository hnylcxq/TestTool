#include "dpu_ckp.h"
#ifdef WIN32
#include "itb_assert.h"
#include <direct.h>
#else
#include <cassert>
#include <unistd.h>
#include <sys/stat.h>
#define ASSERT_ITB(A, B, ...) assert(A)
#endif

void ck_dump(void* ckp)
{
#if DPU_CKP_DISABLE
    return;
#endif
    ckp_c::inst()->dump(ckp);
}


void ckp_c::initial(bool dump_en, std::string fn, int ckp_id)
{
#if DPU_CKP_DISABLE
    return;
#endif
    m_is_dump = dump_en;
    if (!m_is_dump) return;

    if (ckp_id == -1)
    {
        for (int i = 0; i < CK_NUM; i++)
        {
            m_buff[i].initial(i, fn, "cdump");
        }
    }
    else
    {
        m_buff[ckp_id].initial(ckp_id, fn, "cdump");
    }

}

void ckp_c::dump(void* ckp)
{
    if (!m_is_dump)
        return;
    const tag_base* tp = reinterpret_cast<const tag_base*>(ckp);
    switch (tp->m_id)
    {
#include "tag.impl"
    default:
        ASSERT_ITB(0, "unknow checkpoint {}", tp->m_id);
        break;
    }
}

void ckp_c::close(int ckp_id)
{
    if (ckp_id == -1)
    {
        for (int i = 0; i < CK_NUM; i++)
        {
            m_buff[i].close();
        }
    }
    else
    {
        m_buff[ckp_id].close();
    }
}

#include "func.impl"

ckp_c::ckp_c()
{
}

ckp_c::~ckp_c()
{
}


buff_c::buff_c()
{
    memset(m_buff, 0, BUF_SIZE);
}

buff_c::~buff_c()
{
    close();
}

bool exist(std::string _dir)
{
    if (access(_dir.c_str(), 0) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
};


void buff_c::initial(unsigned int id, std::string file_name, std::string dump_dir)
{
    if (dump_dir != "" && !exist(dump_dir))
    {
#ifdef WIN32    
        mkdir(dump_dir.c_str());
#else
        mkdir(dump_dir.c_str(), 0755);
#endif
    }
    m_id = id;

    std::string dump_file = dump_dir == "" ? file_name : dump_dir + "/" + file_name;

    m_fp = fopen(dump_file.c_str(), "w");

    if (m_fp == nullptr)
    {
        assert(0);
    }
}

void buff_c::close()
{
    if (m_offset != 0)
    {
        fwrite(m_buff, m_offset, 1, m_fp);
        fflush(m_fp);
        m_offset = 0;
    }
    if (m_fp != nullptr)
    {
        fclose(m_fp);
        m_fp = nullptr;
    }
}

void buff_c::pushfield(unsigned long long v, unsigned int bits)
{
    int hex_width = (bits + 3) >> 2;
    if (hex_width > 16) ASSERT_ITB(0, "Field bit width exceed, {}", hex_width);

    for (int i = hex_width - 1; i >= 0; i--)
    {
        unsigned char t = (v >> (i * 4)) & 0xf;
        if (m_offset < BUF_SIZE)
        {
            m_buff[m_offset] = g_hex_map_table[t];
        }
        m_offset++;
        if (m_offset == BUF_SIZE)
        {
            fwrite(m_buff, BUF_SIZE, 1, m_fp);
            fflush(m_fp);
            m_offset = 0;
        }
    }
    pushstr(',');
}

void buff_c::pushstr(char c)
{
    m_buff[m_offset++] = c;
    if (m_offset == BUF_SIZE)
    {
        fwrite(m_buff, BUF_SIZE, 1, m_fp);
        fflush(m_fp);
        m_offset = 0;
    }
}


