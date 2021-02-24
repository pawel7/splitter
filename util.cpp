#include <string>

	// conversion from ISO 8859-1 to UTF-8
std::string iso_8859_1_to_utf8(std::string &str)
{
    std::string strOut;
    for (std::string::iterator it = str.begin(); it != str.end(); ++it)
    {
        uint8_t ch = *it;
        if (ch < 0x80) {
            strOut.push_back(ch);
        }
        else {
            strOut.push_back(0xc0 | ch >> 6);
            strOut.push_back(0x80 | (ch & 0x3f));
        }
    }
    return strOut;
}

	// conversion from ISO 8859-2 to UTF-8
std::string iso_8859_2_to_utf8(std::string &str)
{
	std::string strOut;
uint16_t conv[256];
for( int i = 0; i < 128; i++)
	conv[ i ] = i;
conv[ 0x80 ] = 0x0080;	conv[ 0x81 ] = 0x0081;	conv[ 0x82 ] = 0x0082;	conv[ 0x83 ] = 0x0083;	conv[ 0x84 ] = 0x0084;	
conv[ 0x85 ] = 0x0085;	conv[ 0x86 ] = 0x0086;	conv[ 0x87 ] = 0x0087;	conv[ 0x88 ] = 0x0088;	conv[ 0x89 ] = 0x0089;	
conv[ 0x8A ] = 0x008A;	conv[ 0x8B ] = 0x008B;	conv[ 0x8C ] = 0x008C;	conv[ 0x8D ] = 0x008D;	conv[ 0x8E ] = 0x008E;	
conv[ 0x8F ] = 0x008F;	conv[ 0x90 ] = 0x0090;	conv[ 0x91 ] = 0x0091;	conv[ 0x92 ] = 0x0092;	conv[ 0x93 ] = 0x0093;	
conv[ 0x94 ] = 0x0094;	conv[ 0x95 ] = 0x0095;	conv[ 0x96 ] = 0x0096;	conv[ 0x97 ] = 0x0097;	conv[ 0x98 ] = 0x0098;	
conv[ 0x99 ] = 0x0099;	conv[ 0x9A ] = 0x009A;	conv[ 0x9B ] = 0x009B;	conv[ 0x9C ] = 0x009C;	conv[ 0x9D ] = 0x009D;	
conv[ 0x9E ] = 0x009E;	conv[ 0x9F ] = 0x009F;	conv[ 0xA0 ] = 0x00A0;	conv[ 0xA1 ] = 0x0104;	conv[ 0xA2 ] = 0x02D8;	
conv[ 0xA3 ] = 0x0141;	conv[ 0xA4 ] = 0x00A4;	conv[ 0xA5 ] = 0x013D;	conv[ 0xA6 ] = 0x015A;	conv[ 0xA7 ] = 0x00A7;	
conv[ 0xA8 ] = 0x00A8;	conv[ 0xA9 ] = 0x0160;	conv[ 0xAA ] = 0x015E;	conv[ 0xAB ] = 0x0164;	conv[ 0xAC ] = 0x0179;	
conv[ 0xAD ] = 0x00AD;	conv[ 0xAE ] = 0x017D;	conv[ 0xAF ] = 0x017B;	conv[ 0xB0 ] = 0x00B0;	conv[ 0xB1 ] = 0x0105;	
conv[ 0xB2 ] = 0x02DB;	conv[ 0xB3 ] = 0x0142;	conv[ 0xB4 ] = 0x00B4;	conv[ 0xB5 ] = 0x013E;	conv[ 0xB6 ] = 0x015B;	
conv[ 0xB7 ] = 0x02C7;	conv[ 0xB8 ] = 0x00B8;	conv[ 0xB9 ] = 0x0161;	conv[ 0xBA ] = 0x015F;	conv[ 0xBB ] = 0x0165;	
conv[ 0xBC ] = 0x017A;	conv[ 0xBD ] = 0x02DD;	conv[ 0xBE ] = 0x017E;	conv[ 0xBF ] = 0x017C;	conv[ 0xC0 ] = 0x0154;	
conv[ 0xC1 ] = 0x00C1;	conv[ 0xC2 ] = 0x00C2;	conv[ 0xC3 ] = 0x0102;	conv[ 0xC4 ] = 0x00C4;	conv[ 0xC5 ] = 0x0139;	
conv[ 0xC6 ] = 0x0106;	conv[ 0xC7 ] = 0x00C7;	conv[ 0xC8 ] = 0x010C;	conv[ 0xC9 ] = 0x00C9;	conv[ 0xCA ] = 0x0118;	
conv[ 0xCB ] = 0x00CB;	conv[ 0xCC ] = 0x011A;	conv[ 0xCD ] = 0x00CD;	conv[ 0xCE ] = 0x00CE;	conv[ 0xCF ] = 0x010E;	
conv[ 0xD0 ] = 0x0110;	conv[ 0xD1 ] = 0x0143;	conv[ 0xD2 ] = 0x0147;	conv[ 0xD3 ] = 0x00D3;	conv[ 0xD4 ] = 0x00D4;	
conv[ 0xD5 ] = 0x0150;	conv[ 0xD6 ] = 0x00D6;	conv[ 0xD7 ] = 0x00D7;	conv[ 0xD8 ] = 0x0158;	conv[ 0xD9 ] = 0x016E;	
conv[ 0xDA ] = 0x00DA;	conv[ 0xDB ] = 0x0170;	conv[ 0xDC ] = 0x00DC;	conv[ 0xDD ] = 0x00DD;	conv[ 0xDE ] = 0x0162;	
conv[ 0xDF ] = 0x00DF;	conv[ 0xE0 ] = 0x0155;	conv[ 0xE1 ] = 0x00E1;	conv[ 0xE2 ] = 0x00E2;	conv[ 0xE3 ] = 0x0103;	
conv[ 0xE4 ] = 0x00E4;	conv[ 0xE5 ] = 0x013A;	conv[ 0xE6 ] = 0x0107;	conv[ 0xE7 ] = 0x00E7;	conv[ 0xE8 ] = 0x010D;	
conv[ 0xE9 ] = 0x00E9;	conv[ 0xEA ] = 0x0119;	conv[ 0xEB ] = 0x00EB;	conv[ 0xEC ] = 0x011B;	conv[ 0xED ] = 0x00ED;	
conv[ 0xEE ] = 0x00EE;	conv[ 0xEF ] = 0x010F;	conv[ 0xF0 ] = 0x0111;	conv[ 0xF1 ] = 0x0144;	conv[ 0xF2 ] = 0x0148;	
conv[ 0xF3 ] = 0x00F3;	conv[ 0xF4 ] = 0x00F4;	conv[ 0xF5 ] = 0x0151;	conv[ 0xF6 ] = 0x00F6;	conv[ 0xF7 ] = 0x00F7;	
conv[ 0xF8 ] = 0x0159;	conv[ 0xF9 ] = 0x016F;	conv[ 0xFA ] = 0x00FA;	conv[ 0xFB ] = 0x0171;	conv[ 0xFC ] = 0x00FC;	
conv[ 0xFD ] = 0x00FD;	conv[ 0xFE ] = 0x0163;	conv[ 0xFF ] = 0x02D9;	
	
    for (std::string::iterator it = str.begin(); it != str.end(); ++it)
    {
        uint8_t ch = *it;
        if (ch < 0x80) {
            strOut.push_back(ch);
        }
        else {
            strOut.push_back( conv[ch] >> 8   );
            strOut.push_back( conv[ch] & 0xff );
        }
    }
    return strOut;
}
/* UTF-8 to ISO-8859-1/ISO-8859-15 mapper.
 * Return 0..255 for valid ISO-8859-15 code points, 256 otherwise.
*/
static inline unsigned int to_latin9(const unsigned int code)
{
    /* Code points 0 to U+00FF are the same in both. */
    if (code < 256U)
        return code;
    switch (code) {
    case 0x0152U: return 188U; /* U+0152 = 0xBC: OE ligature */
    case 0x0153U: return 189U; /* U+0153 = 0xBD: oe ligature */
    case 0x0160U: return 166U; /* U+0160 = 0xA6: S with caron */
    case 0x0161U: return 168U; /* U+0161 = 0xA8: s with caron */
    case 0x0178U: return 190U; /* U+0178 = 0xBE: Y with diaresis */
    case 0x017DU: return 180U; /* U+017D = 0xB4: Z with caron */
    case 0x017EU: return 184U; /* U+017E = 0xB8: z with caron */
    case 0x20ACU: return 164U; /* U+20AC = 0xA4: Euro */
    default:      return 256U;
    }
}

/* Convert an UTF-8 string to ISO-8859-15.
 * All invalid sequences are ignored.
 * Note: output == input is allowed,
 * but   input < output < input + length
 * is not.
 * Output has to have room for (length+1) chars, including the trailing NUL byte.
 
 https://stackoverflow.com/questions/11156473/is-there-a-way-to-convert-from-utf8-to-iso-8859-1
*/
/*size_t */ std::string utf8_to_latin9(char *const output, const char *const input, const size_t length)
{
    unsigned char             *out = (unsigned char *)output;
    const unsigned char       *in  = (const unsigned char *)input;
    const unsigned char *const end = (const unsigned char *)input + length;
    unsigned int               c;

    while (in < end)
        if (*in < 128)
            *(out++) = *(in++); /* Valid codepoint */
        else
        if (*in < 192)
            in++;               /* 10000000 .. 10111111 are invalid */
        else
        if (*in < 224) {        /* 110xxxxx 10xxxxxx */
            if (in + 1 >= end)
                break;
            if ((in[1] & 192U) == 128U) {
                c = to_latin9( (((unsigned int)(in[0] & 0x1FU)) << 6U)
                             |  ((unsigned int)(in[1] & 0x3FU)) );
                if (c < 256)
                    *(out++) = c;
            }
            in += 2;

        } else
        if (*in < 240) {        /* 1110xxxx 10xxxxxx 10xxxxxx */
            if (in + 2 >= end)
                break;
            if ((in[1] & 192U) == 128U &&
                (in[2] & 192U) == 128U) {
                c = to_latin9( (((unsigned int)(in[0] & 0x0FU)) << 12U)
                             | (((unsigned int)(in[1] & 0x3FU)) << 6U)
                             |  ((unsigned int)(in[2] & 0x3FU)) );
                if (c < 256)
                    *(out++) = c;
            }
            in += 3;

        } else
        if (*in < 248) {        /* 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
            if (in + 3 >= end)
                break;
            if ((in[1] & 192U) == 128U &&
                (in[2] & 192U) == 128U &&
                (in[3] & 192U) == 128U) {
                c = to_latin9( (((unsigned int)(in[0] & 0x07U)) << 18U)
                             | (((unsigned int)(in[1] & 0x3FU)) << 12U)
                             | (((unsigned int)(in[2] & 0x3FU)) << 6U)
                             |  ((unsigned int)(in[3] & 0x3FU)) );
                if (c < 256)
                    *(out++) = c;
            }
            in += 4;

        } else
        if (*in < 252) {        /* 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx */
            if (in + 4 >= end)
                break;
            if ((in[1] & 192U) == 128U &&
                (in[2] & 192U) == 128U &&
                (in[3] & 192U) == 128U &&
                (in[4] & 192U) == 128U) {
                c = to_latin9( (((unsigned int)(in[0] & 0x03U)) << 24U)
                             | (((unsigned int)(in[1] & 0x3FU)) << 18U)
                             | (((unsigned int)(in[2] & 0x3FU)) << 12U)
                             | (((unsigned int)(in[3] & 0x3FU)) << 6U)
                             |  ((unsigned int)(in[4] & 0x3FU)) );
                if (c < 256)
                    *(out++) = c;
            }
            in += 5;

        } else
        if (*in < 254) {        /* 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx */
            if (in + 5 >= end)
                break;
            if ((in[1] & 192U) == 128U &&
                (in[2] & 192U) == 128U &&
                (in[3] & 192U) == 128U &&
                (in[4] & 192U) == 128U &&
                (in[5] & 192U) == 128U) {
                c = to_latin9( (((unsigned int)(in[0] & 0x01U)) << 30U)
                             | (((unsigned int)(in[1] & 0x3FU)) << 24U)
                             | (((unsigned int)(in[2] & 0x3FU)) << 18U)
                             | (((unsigned int)(in[3] & 0x3FU)) << 12U)
                             | (((unsigned int)(in[4] & 0x3FU)) << 6U)
                             |  ((unsigned int)(in[5] & 0x3FU)) );
                if (c < 256)
                    *(out++) = c;
            }
            in += 6;

        } else
            in++;               /* 11111110 and 11111111 are invalid */

    /* Terminate the output string. */
    *out = '\0';

	return std::string(output);
    //return (size_t)(out - (unsigned char *)output);
}
