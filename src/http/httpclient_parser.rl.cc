
#line 1 "httpclient_parser.rl"
/**
*
* Copyright (c) 2010, Zed A. Shaw and Mongrel2 Project Contributors.
* All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
* 
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
* 
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
* 
*     * Neither the name of the Mongrel2 Project, Zed A. Shaw, nor the names
*       of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written
*       permission.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
* IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
* PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "httpclient_parser.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <cerrno>
//#include "dbg.h"

#define LEN(AT, FPC) (FPC - buffer - parser->AT)
#define MARK(M,FPC) (parser->M = (FPC) - buffer)
#define PTR_TO(F) (buffer + parser->F)
#define check(A, M, ...) if(!(A)) { /*log_err(M, ##__VA_ARGS__);*/ errno=0; goto error; }


/** machine **/

#line 157 "httpclient_parser.rl"


/** Data **/

static const int httpclient_parser_start = 1;
static const int httpclient_parser_first_final = 120;
static const int httpclient_parser_error = 0;

static const int httpclient_parser_en_main = 1;

static const char _httpclient_parser_nfa_targs[] = {
	0, 0
};

static const char _httpclient_parser_nfa_offsets[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0
};

static const char _httpclient_parser_nfa_push_actions[] = {
	0, 0
};

static const char _httpclient_parser_nfa_pop_trans[] = {
	0, 0
};


#line 161 "httpclient_parser.rl"


int httpclient_parser_init(httpclient_parser *parser)  {
	int cs = 0;
	
	
	{
		cs = (int)httpclient_parser_start;
	}
	
	#line 166 "httpclient_parser.rl"
	
	
	parser->cs = cs;
	parser->body_start = 0;
	parser->content_len = -1;
	parser->chunked = 0;
	parser->chunks_done = 0;
	parser->mark = 0;
	parser->nread = 0;
	parser->field_len = 0;
	parser->field_start = 0;    
	parser->close = 0;
	
	return(1);
}


/** exec **/
int httpclient_parser_execute(httpclient_parser *parser, const char *buffer, size_t len, size_t off)  
{
	parser->nread = 0;
	parser->mark = 0;
	parser->field_len = 0;
	parser->field_start = 0;
	
	const char *p, *pe;
	int cs = parser->cs;
	
	assert(off <= len && "offset past end of buffer");
	
	p = buffer+off;
	pe = buffer+len;
	
	assert(*pe == '\0' && "pointer does not end on NUL");
	assert(pe - p == (int)len - (int)off && "pointers aren't same distance");
	
	
	
	{
		if ( p == pe )
		goto _test_eof;
		switch ( cs )
		{
			case 1:
			goto st_case_1;
			case 0:
			goto st_case_0;
			case 2:
			goto st_case_2;
			case 120:
			goto st_case_120;
			case 3:
			goto st_case_3;
			case 4:
			goto st_case_4;
			case 5:
			goto st_case_5;
			case 6:
			goto st_case_6;
			case 7:
			goto st_case_7;
			case 8:
			goto st_case_8;
			case 9:
			goto st_case_9;
			case 10:
			goto st_case_10;
			case 11:
			goto st_case_11;
			case 12:
			goto st_case_12;
			case 13:
			goto st_case_13;
			case 14:
			goto st_case_14;
			case 15:
			goto st_case_15;
			case 16:
			goto st_case_16;
			case 17:
			goto st_case_17;
			case 18:
			goto st_case_18;
			case 19:
			goto st_case_19;
			case 20:
			goto st_case_20;
			case 21:
			goto st_case_21;
			case 22:
			goto st_case_22;
			case 23:
			goto st_case_23;
			case 24:
			goto st_case_24;
			case 25:
			goto st_case_25;
			case 26:
			goto st_case_26;
			case 27:
			goto st_case_27;
			case 28:
			goto st_case_28;
			case 29:
			goto st_case_29;
			case 30:
			goto st_case_30;
			case 31:
			goto st_case_31;
			case 32:
			goto st_case_32;
			case 33:
			goto st_case_33;
			case 34:
			goto st_case_34;
			case 35:
			goto st_case_35;
			case 36:
			goto st_case_36;
			case 37:
			goto st_case_37;
			case 38:
			goto st_case_38;
			case 39:
			goto st_case_39;
			case 40:
			goto st_case_40;
			case 41:
			goto st_case_41;
			case 42:
			goto st_case_42;
			case 43:
			goto st_case_43;
			case 44:
			goto st_case_44;
			case 45:
			goto st_case_45;
			case 46:
			goto st_case_46;
			case 47:
			goto st_case_47;
			case 48:
			goto st_case_48;
			case 49:
			goto st_case_49;
			case 50:
			goto st_case_50;
			case 51:
			goto st_case_51;
			case 52:
			goto st_case_52;
			case 53:
			goto st_case_53;
			case 54:
			goto st_case_54;
			case 55:
			goto st_case_55;
			case 56:
			goto st_case_56;
			case 57:
			goto st_case_57;
			case 58:
			goto st_case_58;
			case 59:
			goto st_case_59;
			case 60:
			goto st_case_60;
			case 61:
			goto st_case_61;
			case 62:
			goto st_case_62;
			case 63:
			goto st_case_63;
			case 64:
			goto st_case_64;
			case 65:
			goto st_case_65;
			case 66:
			goto st_case_66;
			case 67:
			goto st_case_67;
			case 68:
			goto st_case_68;
			case 69:
			goto st_case_69;
			case 70:
			goto st_case_70;
			case 71:
			goto st_case_71;
			case 121:
			goto st_case_121;
			case 72:
			goto st_case_72;
			case 73:
			goto st_case_73;
			case 74:
			goto st_case_74;
			case 75:
			goto st_case_75;
			case 76:
			goto st_case_76;
			case 77:
			goto st_case_77;
			case 78:
			goto st_case_78;
			case 79:
			goto st_case_79;
			case 80:
			goto st_case_80;
			case 81:
			goto st_case_81;
			case 82:
			goto st_case_82;
			case 83:
			goto st_case_83;
			case 84:
			goto st_case_84;
			case 85:
			goto st_case_85;
			case 86:
			goto st_case_86;
			case 87:
			goto st_case_87;
			case 88:
			goto st_case_88;
			case 122:
			goto st_case_122;
			case 89:
			goto st_case_89;
			case 90:
			goto st_case_90;
			case 91:
			goto st_case_91;
			case 92:
			goto st_case_92;
			case 93:
			goto st_case_93;
			case 94:
			goto st_case_94;
			case 95:
			goto st_case_95;
			case 96:
			goto st_case_96;
			case 97:
			goto st_case_97;
			case 98:
			goto st_case_98;
			case 99:
			goto st_case_99;
			case 100:
			goto st_case_100;
			case 101:
			goto st_case_101;
			case 102:
			goto st_case_102;
			case 103:
			goto st_case_103;
			case 104:
			goto st_case_104;
			case 105:
			goto st_case_105;
			case 106:
			goto st_case_106;
			case 107:
			goto st_case_107;
			case 108:
			goto st_case_108;
			case 109:
			goto st_case_109;
			case 110:
			goto st_case_110;
			case 111:
			goto st_case_111;
			case 112:
			goto st_case_112;
			case 113:
			goto st_case_113;
			case 114:
			goto st_case_114;
			case 115:
			goto st_case_115;
			case 123:
			goto st_case_123;
			case 116:
			goto st_case_116;
			case 117:
			goto st_case_117;
			case 118:
			goto st_case_118;
			case 119:
			goto st_case_119;
		}
		goto st_out;
		st_case_1:
		if ( ( (*( p))) == 72 ) {
			goto ctr2;
		}
		if ( ( (*( p))) < 65 ) {
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto ctr0;
			}
		} else if ( ( (*( p))) > 70 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 102 ) {
				goto ctr0;
			}
		} else {
			goto ctr0;
		}
		{
			goto st0;
		}
		st_case_0:
		st0:
		cs = 0;
		goto _out;
		ctr0:
		{
			#line 54 "httpclient_parser.rl"
			MARK(mark, p); }
		
		goto st2;
		st2:
		p+= 1;
		if ( p == pe )
		goto _test_eof2;
		st_case_2:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr3;
			}
			case 13: {
				goto ctr4;
			}
			case 59: {
				goto ctr6;
			}
		}
		if ( ( (*( p))) < 65 ) {
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto st2;
			}
		} else if ( ( (*( p))) > 70 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 102 ) {
				goto st2;
			}
		} else {
			goto st2;
		}
		{
			goto st0;
		}
		ctr3:
		{
			#line 95 "httpclient_parser.rl"
			
			parser->chunked = 1;
			parser->content_len = strtol(PTR_TO(mark), NULL, 16);
			parser->chunks_done = parser->content_len <= 0;
			
			if(parser->chunks_done && parser->last_chunk) {
				parser->last_chunk(parser->data, PTR_TO(mark), LEN(mark, p));
			} else if(parser->chunk_size != NULL) {
				parser->chunk_size(parser->data, PTR_TO(mark), LEN(mark, p));
			} // else skip it
		}
		{
			#line 111 "httpclient_parser.rl"
			
			parser->body_start = p - buffer + 1; 
			if(parser->header_done != NULL)
			parser->header_done(parser->data, p + 1, pe - p - 1);
			{p+= 1; cs = 120; goto _out;}
		}
		
		goto st120;
		ctr7:
		{
			#line 111 "httpclient_parser.rl"
			
			parser->body_start = p - buffer + 1; 
			if(parser->header_done != NULL)
			parser->header_done(parser->data, p + 1, pe - p - 1);
			{p+= 1; cs = 120; goto _out;}
		}
		
		goto st120;
		ctr9:
		{
			#line 58 "httpclient_parser.rl"
			
			parser->field_len = LEN(field_start, p);
		}
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		{
			#line 111 "httpclient_parser.rl"
			
			parser->body_start = p - buffer + 1; 
			if(parser->header_done != NULL)
			parser->header_done(parser->data, p + 1, pe - p - 1);
			{p+= 1; cs = 120; goto _out;}
		}
		
		goto st120;
		ctr15:
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		{
			#line 111 "httpclient_parser.rl"
			
			parser->body_start = p - buffer + 1; 
			if(parser->header_done != NULL)
			parser->header_done(parser->data, p + 1, pe - p - 1);
			{p+= 1; cs = 120; goto _out;}
		}
		
		goto st120;
		ctr74:
		{
			#line 68 "httpclient_parser.rl"
			
			parser->close = 1;
		}
		{
			#line 111 "httpclient_parser.rl"
			
			parser->body_start = p - buffer + 1; 
			if(parser->header_done != NULL)
			parser->header_done(parser->data, p + 1, pe - p - 1);
			{p+= 1; cs = 120; goto _out;}
		}
		
		goto st120;
		st120:
		p+= 1;
		if ( p == pe )
		goto _test_eof120;
		st_case_120:
		{
			goto st0;
		}
		ctr4:
		{
			#line 95 "httpclient_parser.rl"
			
			parser->chunked = 1;
			parser->content_len = strtol(PTR_TO(mark), NULL, 16);
			parser->chunks_done = parser->content_len <= 0;
			
			if(parser->chunks_done && parser->last_chunk) {
				parser->last_chunk(parser->data, PTR_TO(mark), LEN(mark, p));
			} else if(parser->chunk_size != NULL) {
				parser->chunk_size(parser->data, PTR_TO(mark), LEN(mark, p));
			} // else skip it
		}
		
		goto st3;
		ctr10:
		{
			#line 58 "httpclient_parser.rl"
			
			parser->field_len = LEN(field_start, p);
		}
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st3;
		ctr16:
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st3;
		ctr75:
		{
			#line 68 "httpclient_parser.rl"
			
			parser->close = 1;
		}
		
		goto st3;
		st3:
		p+= 1;
		if ( p == pe )
		goto _test_eof3;
		st_case_3:
		if ( ( (*( p))) == 10 ) {
			goto ctr7;
		}
		{
			goto st0;
		}
		ctr6:
		{
			#line 95 "httpclient_parser.rl"
			
			parser->chunked = 1;
			parser->content_len = strtol(PTR_TO(mark), NULL, 16);
			parser->chunks_done = parser->content_len <= 0;
			
			if(parser->chunks_done && parser->last_chunk) {
				parser->last_chunk(parser->data, PTR_TO(mark), LEN(mark, p));
			} else if(parser->chunk_size != NULL) {
				parser->chunk_size(parser->data, PTR_TO(mark), LEN(mark, p));
			} // else skip it
		}
		
		goto st4;
		ctr12:
		{
			#line 58 "httpclient_parser.rl"
			
			parser->field_len = LEN(field_start, p);
		}
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st4;
		ctr18:
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st4;
		st4:
		p+= 1;
		if ( p == pe )
		goto _test_eof4;
		st_case_4:
		switch( ( (*( p))) ) {
			case 33: {
				goto ctr8;
			}
			case 124: {
				goto ctr8;
			}
			case 126: {
				goto ctr8;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto ctr8;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto ctr8;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto ctr8;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto ctr8;
				}
			} else {
				goto ctr8;
			}
		} else {
			goto ctr8;
		}
		{
			goto st0;
		}
		ctr8:
		{
			#line 56 "httpclient_parser.rl"
			MARK(field_start, p); }
		
		goto st5;
		st5:
		p+= 1;
		if ( p == pe )
		goto _test_eof5;
		st_case_5:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr9;
			}
			case 13: {
				goto ctr10;
			}
			case 33: {
				goto st5;
			}
			case 59: {
				goto ctr12;
			}
			case 61: {
				goto ctr13;
			}
			case 124: {
				goto st5;
			}
			case 126: {
				goto st5;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st5;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st5;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st5;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st5;
				}
			} else {
				goto st5;
			}
		} else {
			goto st5;
		}
		{
			goto st0;
		}
		ctr13:
		{
			#line 58 "httpclient_parser.rl"
			
			parser->field_len = LEN(field_start, p);
		}
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		
		goto st6;
		st6:
		p+= 1;
		if ( p == pe )
		goto _test_eof6;
		st_case_6:
		switch( ( (*( p))) ) {
			case 33: {
				goto ctr14;
			}
			case 124: {
				goto ctr14;
			}
			case 126: {
				goto ctr14;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto ctr14;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto ctr14;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto ctr14;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto ctr14;
				}
			} else {
				goto ctr14;
			}
		} else {
			goto ctr14;
		}
		{
			goto st0;
		}
		ctr14:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		
		goto st7;
		st7:
		p+= 1;
		if ( p == pe )
		goto _test_eof7;
		st_case_7:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr15;
			}
			case 13: {
				goto ctr16;
			}
			case 33: {
				goto st7;
			}
			case 59: {
				goto ctr18;
			}
			case 124: {
				goto st7;
			}
			case 126: {
				goto st7;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st7;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st7;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st7;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st7;
				}
			} else {
				goto st7;
			}
		} else {
			goto st7;
		}
		{
			goto st0;
		}
		ctr2:
		{
			#line 54 "httpclient_parser.rl"
			MARK(mark, p); }
		
		goto st8;
		st8:
		p+= 1;
		if ( p == pe )
		goto _test_eof8;
		st_case_8:
		if ( ( (*( p))) == 84 ) {
			goto st9;
		}
		{
			goto st0;
		}
		st9:
		p+= 1;
		if ( p == pe )
		goto _test_eof9;
		st_case_9:
		if ( ( (*( p))) == 84 ) {
			goto st10;
		}
		{
			goto st0;
		}
		st10:
		p+= 1;
		if ( p == pe )
		goto _test_eof10;
		st_case_10:
		if ( ( (*( p))) == 80 ) {
			goto st11;
		}
		{
			goto st0;
		}
		st11:
		p+= 1;
		if ( p == pe )
		goto _test_eof11;
		st_case_11:
		if ( ( (*( p))) == 47 ) {
			goto st12;
		}
		{
			goto st0;
		}
		st12:
		p+= 1;
		if ( p == pe )
		goto _test_eof12;
		st_case_12:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto st13;
		}
		{
			goto st0;
		}
		st13:
		p+= 1;
		if ( p == pe )
		goto _test_eof13;
		st_case_13:
		if ( ( (*( p))) == 46 ) {
			goto st14;
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto st13;
		}
		{
			goto st0;
		}
		st14:
		p+= 1;
		if ( p == pe )
		goto _test_eof14;
		st_case_14:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto st15;
		}
		{
			goto st0;
		}
		st15:
		p+= 1;
		if ( p == pe )
		goto _test_eof15;
		st_case_15:
		if ( ( (*( p))) == 32 ) {
			goto ctr26;
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto st15;
		}
		{
			goto st0;
		}
		ctr26:
		{
			#line 90 "httpclient_parser.rl"
			
			if(parser->http_version != NULL)
			parser->http_version(parser->data, PTR_TO(mark), LEN(mark, p));
		}
		
		goto st16;
		st16:
		p+= 1;
		if ( p == pe )
		goto _test_eof16;
		st_case_16:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto ctr27;
		}
		{
			goto st0;
		}
		ctr27:
		{
			#line 54 "httpclient_parser.rl"
			MARK(mark, p); }
		
		goto st17;
		st17:
		p+= 1;
		if ( p == pe )
		goto _test_eof17;
		st_case_17:
		if ( ( (*( p))) == 32 ) {
			goto ctr28;
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto st17;
		}
		{
			goto st0;
		}
		ctr28:
		{
			#line 83 "httpclient_parser.rl"
			
			parser->status = strtol(PTR_TO(mark), NULL, 10);
			
			if(parser->status_code != NULL)
			parser->status_code(parser->data, PTR_TO(mark), LEN(mark, p));
		}
		
		goto st18;
		st18:
		p+= 1;
		if ( p == pe )
		goto _test_eof18;
		st_case_18:
		if ( ( (*( p))) == 10 ) {
			goto st0;
		}
		{
			goto ctr30;
		}
		ctr30:
		{
			#line 54 "httpclient_parser.rl"
			MARK(mark, p); }
		
		goto st19;
		st19:
		p+= 1;
		if ( p == pe )
		goto _test_eof19;
		st_case_19:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr32;
			}
			case 13: {
				goto ctr33;
			}
		}
		{
			goto st19;
		}
		ctr45:
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st20;
		ctr32:
		{
			#line 78 "httpclient_parser.rl"
			
			if(parser->reason_phrase != NULL)
			parser->reason_phrase(parser->data, PTR_TO(mark), LEN(mark, p));
		}
		
		goto st20;
		ctr42:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st20;
		ctr111:
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		{
			#line 107 "httpclient_parser.rl"
			
			parser->chunked = 1;
		}
		
		goto st20;
		ctr113:
		{
			#line 107 "httpclient_parser.rl"
			
			parser->chunked = 1;
		}
		
		goto st20;
		ctr158:
		{
			#line 64 "httpclient_parser.rl"
			
			parser->content_len = strtol(PTR_TO(mark), NULL, 10);
		}
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st20;
		st20:
		p+= 1;
		if ( p == pe )
		goto _test_eof20;
		st_case_20:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr7;
			}
			case 13: {
				goto st3;
			}
			case 33: {
				goto ctr35;
			}
			case 67: {
				goto ctr36;
			}
			case 84: {
				goto ctr37;
			}
			case 99: {
				goto ctr36;
			}
			case 116: {
				goto ctr37;
			}
			case 124: {
				goto ctr35;
			}
			case 126: {
				goto ctr35;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto ctr35;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto ctr35;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto ctr35;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto ctr35;
				}
			} else {
				goto ctr35;
			}
		} else {
			goto ctr35;
		}
		{
			goto st0;
		}
		ctr35:
		{
			#line 56 "httpclient_parser.rl"
			MARK(field_start, p); }
		
		goto st21;
		ctr76:
		{
			#line 68 "httpclient_parser.rl"
			
			parser->close = 1;
		}
		{
			#line 56 "httpclient_parser.rl"
			MARK(field_start, p); }
		
		goto st21;
		st21:
		p+= 1;
		if ( p == pe )
		goto _test_eof21;
		st_case_21:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		ctr41:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		
		goto st22;
		ctr39:
		{
			#line 58 "httpclient_parser.rl"
			
			parser->field_len = LEN(field_start, p);
		}
		
		goto st22;
		st22:
		p+= 1;
		if ( p == pe )
		goto _test_eof22;
		st_case_22:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr42;
			}
			case 13: {
				goto ctr43;
			}
			case 32: {
				goto ctr41;
			}
		}
		if ( 9 <= ( (*( p))) && ( (*( p))) <= 12 ) {
			goto ctr41;
		}
		{
			goto ctr40;
		}
		ctr40:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		
		goto st23;
		st23:
		p+= 1;
		if ( p == pe )
		goto _test_eof23;
		st_case_23:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr45;
			}
			case 13: {
				goto ctr46;
			}
		}
		{
			goto st23;
		}
		ctr46:
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st24;
		ctr33:
		{
			#line 78 "httpclient_parser.rl"
			
			if(parser->reason_phrase != NULL)
			parser->reason_phrase(parser->data, PTR_TO(mark), LEN(mark, p));
		}
		
		goto st24;
		ctr43:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st24;
		ctr159:
		{
			#line 64 "httpclient_parser.rl"
			
			parser->content_len = strtol(PTR_TO(mark), NULL, 10);
		}
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st24;
		st24:
		p+= 1;
		if ( p == pe )
		goto _test_eof24;
		st_case_24:
		if ( ( (*( p))) == 10 ) {
			goto st20;
		}
		{
			goto st0;
		}
		ctr36:
		{
			#line 56 "httpclient_parser.rl"
			MARK(field_start, p); }
		
		goto st25;
		ctr77:
		{
			#line 68 "httpclient_parser.rl"
			
			parser->close = 1;
		}
		{
			#line 56 "httpclient_parser.rl"
			MARK(field_start, p); }
		
		goto st25;
		st25:
		p+= 1;
		if ( p == pe )
		goto _test_eof25;
		st_case_25:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 79: {
				goto st26;
			}
			case 111: {
				goto st26;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st26:
		p+= 1;
		if ( p == pe )
		goto _test_eof26;
		st_case_26:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 78: {
				goto st27;
			}
			case 110: {
				goto st27;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st27:
		p+= 1;
		if ( p == pe )
		goto _test_eof27;
		st_case_27:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 78: {
				goto st28;
			}
			case 84: {
				goto st101;
			}
			case 110: {
				goto st28;
			}
			case 116: {
				goto st101;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st28:
		p+= 1;
		if ( p == pe )
		goto _test_eof28;
		st_case_28:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 69: {
				goto st29;
			}
			case 101: {
				goto st29;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st29:
		p+= 1;
		if ( p == pe )
		goto _test_eof29;
		st_case_29:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 67: {
				goto st30;
			}
			case 99: {
				goto st30;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st30:
		p+= 1;
		if ( p == pe )
		goto _test_eof30;
		st_case_30:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 84: {
				goto st31;
			}
			case 116: {
				goto st31;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st31:
		p+= 1;
		if ( p == pe )
		goto _test_eof31;
		st_case_31:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 73: {
				goto st32;
			}
			case 105: {
				goto st32;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st32:
		p+= 1;
		if ( p == pe )
		goto _test_eof32;
		st_case_32:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 79: {
				goto st33;
			}
			case 111: {
				goto st33;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st33:
		p+= 1;
		if ( p == pe )
		goto _test_eof33;
		st_case_33:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 78: {
				goto st34;
			}
			case 110: {
				goto st34;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st34:
		p+= 1;
		if ( p == pe )
		goto _test_eof34;
		st_case_34:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr58;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		ctr59:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		
		goto st35;
		ctr58:
		{
			#line 58 "httpclient_parser.rl"
			
			parser->field_len = LEN(field_start, p);
		}
		
		goto st35;
		st35:
		p+= 1;
		if ( p == pe )
		goto _test_eof35;
		st_case_35:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr60;
			}
			case 13: {
				goto ctr61;
			}
			case 32: {
				goto ctr59;
			}
			case 67: {
				goto ctr62;
			}
			case 99: {
				goto ctr62;
			}
		}
		if ( 9 <= ( (*( p))) && ( (*( p))) <= 12 ) {
			goto ctr59;
		}
		{
			goto ctr40;
		}
		ctr60:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st36;
		st36:
		p+= 1;
		if ( p == pe )
		goto _test_eof36;
		st_case_36:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr64;
			}
			case 13: {
				goto st89;
			}
			case 32: {
				goto st37;
			}
			case 33: {
				goto ctr35;
			}
			case 67: {
				goto ctr66;
			}
			case 84: {
				goto ctr37;
			}
			case 99: {
				goto ctr66;
			}
			case 116: {
				goto ctr37;
			}
			case 124: {
				goto ctr35;
			}
			case 126: {
				goto ctr35;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) < 35 ) {
				if ( 9 <= ( (*( p))) && ( (*( p))) <= 12 ) {
					goto st37;
				}
			} else if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto ctr35;
				}
			} else {
				goto ctr35;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto ctr35;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto ctr35;
				}
			} else {
				goto ctr35;
			}
		} else {
			goto ctr35;
		}
		{
			goto st0;
		}
		st37:
		p+= 1;
		if ( p == pe )
		goto _test_eof37;
		st_case_37:
		switch( ( (*( p))) ) {
			case 32: {
				goto st37;
			}
			case 67: {
				goto st38;
			}
			case 99: {
				goto st38;
			}
		}
		if ( 9 <= ( (*( p))) && ( (*( p))) <= 13 ) {
			goto st37;
		}
		{
			goto st0;
		}
		st38:
		p+= 1;
		if ( p == pe )
		goto _test_eof38;
		st_case_38:
		switch( ( (*( p))) ) {
			case 76: {
				goto st39;
			}
			case 108: {
				goto st39;
			}
		}
		{
			goto st0;
		}
		st39:
		p+= 1;
		if ( p == pe )
		goto _test_eof39;
		st_case_39:
		switch( ( (*( p))) ) {
			case 79: {
				goto st40;
			}
			case 111: {
				goto st40;
			}
		}
		{
			goto st0;
		}
		st40:
		p+= 1;
		if ( p == pe )
		goto _test_eof40;
		st_case_40:
		switch( ( (*( p))) ) {
			case 83: {
				goto st41;
			}
			case 115: {
				goto st41;
			}
		}
		{
			goto st0;
		}
		st41:
		p+= 1;
		if ( p == pe )
		goto _test_eof41;
		st_case_41:
		switch( ( (*( p))) ) {
			case 69: {
				goto st42;
			}
			case 101: {
				goto st42;
			}
		}
		{
			goto st0;
		}
		st42:
		p+= 1;
		if ( p == pe )
		goto _test_eof42;
		st_case_42:
		switch( ( (*( p))) ) {
			case 10: {
				goto st43;
			}
			case 13: {
				goto st88;
			}
		}
		{
			goto st0;
		}
		ctr136:
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st43;
		st43:
		p+= 1;
		if ( p == pe )
		goto _test_eof43;
		st_case_43:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr74;
			}
			case 13: {
				goto ctr75;
			}
			case 33: {
				goto ctr76;
			}
			case 67: {
				goto ctr77;
			}
			case 84: {
				goto ctr78;
			}
			case 99: {
				goto ctr77;
			}
			case 116: {
				goto ctr78;
			}
			case 124: {
				goto ctr76;
			}
			case 126: {
				goto ctr76;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto ctr76;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto ctr76;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto ctr76;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto ctr76;
				}
			} else {
				goto ctr76;
			}
		} else {
			goto ctr76;
		}
		{
			goto st0;
		}
		ctr37:
		{
			#line 56 "httpclient_parser.rl"
			MARK(field_start, p); }
		
		goto st44;
		ctr78:
		{
			#line 68 "httpclient_parser.rl"
			
			parser->close = 1;
		}
		{
			#line 56 "httpclient_parser.rl"
			MARK(field_start, p); }
		
		goto st44;
		st44:
		p+= 1;
		if ( p == pe )
		goto _test_eof44;
		st_case_44:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 82: {
				goto st45;
			}
			case 114: {
				goto st45;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st45:
		p+= 1;
		if ( p == pe )
		goto _test_eof45;
		st_case_45:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 65: {
				goto st46;
			}
			case 97: {
				goto st46;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 66 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st46:
		p+= 1;
		if ( p == pe )
		goto _test_eof46;
		st_case_46:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 78: {
				goto st47;
			}
			case 110: {
				goto st47;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st47:
		p+= 1;
		if ( p == pe )
		goto _test_eof47;
		st_case_47:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 83: {
				goto st48;
			}
			case 115: {
				goto st48;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st48:
		p+= 1;
		if ( p == pe )
		goto _test_eof48;
		st_case_48:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 70: {
				goto st49;
			}
			case 102: {
				goto st49;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st49:
		p+= 1;
		if ( p == pe )
		goto _test_eof49;
		st_case_49:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 69: {
				goto st50;
			}
			case 101: {
				goto st50;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st50:
		p+= 1;
		if ( p == pe )
		goto _test_eof50;
		st_case_50:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 82: {
				goto st51;
			}
			case 114: {
				goto st51;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st51:
		p+= 1;
		if ( p == pe )
		goto _test_eof51;
		st_case_51:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 45: {
				goto st52;
			}
			case 46: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 48 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 57 ) {
			if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 65 ) {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st52:
		p+= 1;
		if ( p == pe )
		goto _test_eof52;
		st_case_52:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 69: {
				goto st53;
			}
			case 101: {
				goto st53;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st53:
		p+= 1;
		if ( p == pe )
		goto _test_eof53;
		st_case_53:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 78: {
				goto st54;
			}
			case 110: {
				goto st54;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st54:
		p+= 1;
		if ( p == pe )
		goto _test_eof54;
		st_case_54:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 67: {
				goto st55;
			}
			case 99: {
				goto st55;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st55:
		p+= 1;
		if ( p == pe )
		goto _test_eof55;
		st_case_55:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 79: {
				goto st56;
			}
			case 111: {
				goto st56;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st56:
		p+= 1;
		if ( p == pe )
		goto _test_eof56;
		st_case_56:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 68: {
				goto st57;
			}
			case 100: {
				goto st57;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st57:
		p+= 1;
		if ( p == pe )
		goto _test_eof57;
		st_case_57:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 73: {
				goto st58;
			}
			case 105: {
				goto st58;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st58:
		p+= 1;
		if ( p == pe )
		goto _test_eof58;
		st_case_58:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 78: {
				goto st59;
			}
			case 110: {
				goto st59;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st59:
		p+= 1;
		if ( p == pe )
		goto _test_eof59;
		st_case_59:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 71: {
				goto st60;
			}
			case 103: {
				goto st60;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st60:
		p+= 1;
		if ( p == pe )
		goto _test_eof60;
		st_case_60:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr95;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		ctr96:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		
		goto st61;
		ctr95:
		{
			#line 58 "httpclient_parser.rl"
			
			parser->field_len = LEN(field_start, p);
		}
		
		goto st61;
		st61:
		p+= 1;
		if ( p == pe )
		goto _test_eof61;
		st_case_61:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr97;
			}
			case 13: {
				goto ctr98;
			}
			case 32: {
				goto ctr96;
			}
			case 67: {
				goto ctr99;
			}
			case 99: {
				goto ctr99;
			}
		}
		if ( 9 <= ( (*( p))) && ( (*( p))) <= 12 ) {
			goto ctr96;
		}
		{
			goto ctr40;
		}
		ctr97:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st62;
		st62:
		p+= 1;
		if ( p == pe )
		goto _test_eof62;
		st_case_62:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr101;
			}
			case 13: {
				goto st72;
			}
			case 32: {
				goto st63;
			}
			case 33: {
				goto ctr35;
			}
			case 67: {
				goto ctr103;
			}
			case 84: {
				goto ctr37;
			}
			case 99: {
				goto ctr103;
			}
			case 116: {
				goto ctr37;
			}
			case 124: {
				goto ctr35;
			}
			case 126: {
				goto ctr35;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) < 35 ) {
				if ( 9 <= ( (*( p))) && ( (*( p))) <= 12 ) {
					goto st63;
				}
			} else if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto ctr35;
				}
			} else {
				goto ctr35;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto ctr35;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto ctr35;
				}
			} else {
				goto ctr35;
			}
		} else {
			goto ctr35;
		}
		{
			goto st0;
		}
		st63:
		p+= 1;
		if ( p == pe )
		goto _test_eof63;
		st_case_63:
		switch( ( (*( p))) ) {
			case 32: {
				goto st63;
			}
			case 67: {
				goto ctr104;
			}
			case 99: {
				goto ctr104;
			}
		}
		if ( 9 <= ( (*( p))) && ( (*( p))) <= 13 ) {
			goto st63;
		}
		{
			goto st0;
		}
		ctr104:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		
		goto st64;
		st64:
		p+= 1;
		if ( p == pe )
		goto _test_eof64;
		st_case_64:
		switch( ( (*( p))) ) {
			case 72: {
				goto st65;
			}
			case 104: {
				goto st65;
			}
		}
		{
			goto st0;
		}
		st65:
		p+= 1;
		if ( p == pe )
		goto _test_eof65;
		st_case_65:
		switch( ( (*( p))) ) {
			case 85: {
				goto st66;
			}
			case 117: {
				goto st66;
			}
		}
		{
			goto st0;
		}
		st66:
		p+= 1;
		if ( p == pe )
		goto _test_eof66;
		st_case_66:
		switch( ( (*( p))) ) {
			case 78: {
				goto st67;
			}
			case 110: {
				goto st67;
			}
		}
		{
			goto st0;
		}
		st67:
		p+= 1;
		if ( p == pe )
		goto _test_eof67;
		st_case_67:
		switch( ( (*( p))) ) {
			case 75: {
				goto st68;
			}
			case 107: {
				goto st68;
			}
		}
		{
			goto st0;
		}
		st68:
		p+= 1;
		if ( p == pe )
		goto _test_eof68;
		st_case_68:
		switch( ( (*( p))) ) {
			case 69: {
				goto st69;
			}
			case 101: {
				goto st69;
			}
		}
		{
			goto st0;
		}
		st69:
		p+= 1;
		if ( p == pe )
		goto _test_eof69;
		st_case_69:
		switch( ( (*( p))) ) {
			case 68: {
				goto st70;
			}
			case 100: {
				goto st70;
			}
		}
		{
			goto st0;
		}
		st70:
		p+= 1;
		if ( p == pe )
		goto _test_eof70;
		st_case_70:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr111;
			}
			case 13: {
				goto ctr112;
			}
		}
		{
			goto st0;
		}
		ctr112:
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st71;
		st71:
		p+= 1;
		if ( p == pe )
		goto _test_eof71;
		st_case_71:
		if ( ( (*( p))) == 10 ) {
			goto ctr113;
		}
		{
			goto st0;
		}
		ctr101:
		{
			#line 111 "httpclient_parser.rl"
			
			parser->body_start = p - buffer + 1; 
			if(parser->header_done != NULL)
			parser->header_done(parser->data, p + 1, pe - p - 1);
			{p+= 1; cs = 121; goto _out;}
		}
		
		goto st121;
		st121:
		p+= 1;
		if ( p == pe )
		goto _test_eof121;
		st_case_121:
		switch( ( (*( p))) ) {
			case 32: {
				goto st63;
			}
			case 67: {
				goto ctr104;
			}
			case 99: {
				goto ctr104;
			}
		}
		if ( 9 <= ( (*( p))) && ( (*( p))) <= 13 ) {
			goto st63;
		}
		{
			goto st0;
		}
		st72:
		p+= 1;
		if ( p == pe )
		goto _test_eof72;
		st_case_72:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr101;
			}
			case 32: {
				goto st63;
			}
			case 67: {
				goto ctr104;
			}
			case 99: {
				goto ctr104;
			}
		}
		if ( 9 <= ( (*( p))) && ( (*( p))) <= 13 ) {
			goto st63;
		}
		{
			goto st0;
		}
		ctr103:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		{
			#line 56 "httpclient_parser.rl"
			MARK(field_start, p); }
		
		goto st73;
		st73:
		p+= 1;
		if ( p == pe )
		goto _test_eof73;
		st_case_73:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 72: {
				goto st74;
			}
			case 79: {
				goto st26;
			}
			case 104: {
				goto st74;
			}
			case 111: {
				goto st26;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st74:
		p+= 1;
		if ( p == pe )
		goto _test_eof74;
		st_case_74:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 85: {
				goto st75;
			}
			case 117: {
				goto st75;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st75:
		p+= 1;
		if ( p == pe )
		goto _test_eof75;
		st_case_75:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 78: {
				goto st76;
			}
			case 110: {
				goto st76;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st76:
		p+= 1;
		if ( p == pe )
		goto _test_eof76;
		st_case_76:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 75: {
				goto st77;
			}
			case 107: {
				goto st77;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st77:
		p+= 1;
		if ( p == pe )
		goto _test_eof77;
		st_case_77:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 69: {
				goto st78;
			}
			case 101: {
				goto st78;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st78:
		p+= 1;
		if ( p == pe )
		goto _test_eof78;
		st_case_78:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 68: {
				goto st79;
			}
			case 100: {
				goto st79;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st79:
		p+= 1;
		if ( p == pe )
		goto _test_eof79;
		st_case_79:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr111;
			}
			case 13: {
				goto ctr112;
			}
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		ctr98:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st80;
		st80:
		p+= 1;
		if ( p == pe )
		goto _test_eof80;
		st_case_80:
		switch( ( (*( p))) ) {
			case 10: {
				goto st62;
			}
			case 32: {
				goto st63;
			}
			case 67: {
				goto ctr104;
			}
			case 99: {
				goto ctr104;
			}
		}
		if ( 9 <= ( (*( p))) && ( (*( p))) <= 13 ) {
			goto st63;
		}
		{
			goto st0;
		}
		ctr99:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		
		goto st81;
		st81:
		p+= 1;
		if ( p == pe )
		goto _test_eof81;
		st_case_81:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr45;
			}
			case 13: {
				goto ctr46;
			}
			case 72: {
				goto st82;
			}
			case 104: {
				goto st82;
			}
		}
		{
			goto st23;
		}
		st82:
		p+= 1;
		if ( p == pe )
		goto _test_eof82;
		st_case_82:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr45;
			}
			case 13: {
				goto ctr46;
			}
			case 85: {
				goto st83;
			}
			case 117: {
				goto st83;
			}
		}
		{
			goto st23;
		}
		st83:
		p+= 1;
		if ( p == pe )
		goto _test_eof83;
		st_case_83:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr45;
			}
			case 13: {
				goto ctr46;
			}
			case 78: {
				goto st84;
			}
			case 110: {
				goto st84;
			}
		}
		{
			goto st23;
		}
		st84:
		p+= 1;
		if ( p == pe )
		goto _test_eof84;
		st_case_84:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr45;
			}
			case 13: {
				goto ctr46;
			}
			case 75: {
				goto st85;
			}
			case 107: {
				goto st85;
			}
		}
		{
			goto st23;
		}
		st85:
		p+= 1;
		if ( p == pe )
		goto _test_eof85;
		st_case_85:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr45;
			}
			case 13: {
				goto ctr46;
			}
			case 69: {
				goto st86;
			}
			case 101: {
				goto st86;
			}
		}
		{
			goto st23;
		}
		st86:
		p+= 1;
		if ( p == pe )
		goto _test_eof86;
		st_case_86:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr45;
			}
			case 13: {
				goto ctr46;
			}
			case 68: {
				goto st87;
			}
			case 100: {
				goto st87;
			}
		}
		{
			goto st23;
		}
		st87:
		p+= 1;
		if ( p == pe )
		goto _test_eof87;
		st_case_87:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr111;
			}
			case 13: {
				goto ctr112;
			}
		}
		{
			goto st23;
		}
		ctr137:
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st88;
		st88:
		p+= 1;
		if ( p == pe )
		goto _test_eof88;
		st_case_88:
		if ( ( (*( p))) == 10 ) {
			goto st43;
		}
		{
			goto st0;
		}
		ctr64:
		{
			#line 111 "httpclient_parser.rl"
			
			parser->body_start = p - buffer + 1; 
			if(parser->header_done != NULL)
			parser->header_done(parser->data, p + 1, pe - p - 1);
			{p+= 1; cs = 122; goto _out;}
		}
		
		goto st122;
		st122:
		p+= 1;
		if ( p == pe )
		goto _test_eof122;
		st_case_122:
		switch( ( (*( p))) ) {
			case 32: {
				goto st37;
			}
			case 67: {
				goto st38;
			}
			case 99: {
				goto st38;
			}
		}
		if ( 9 <= ( (*( p))) && ( (*( p))) <= 13 ) {
			goto st37;
		}
		{
			goto st0;
		}
		st89:
		p+= 1;
		if ( p == pe )
		goto _test_eof89;
		st_case_89:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr64;
			}
			case 32: {
				goto st37;
			}
			case 67: {
				goto st38;
			}
			case 99: {
				goto st38;
			}
		}
		if ( 9 <= ( (*( p))) && ( (*( p))) <= 13 ) {
			goto st37;
		}
		{
			goto st0;
		}
		ctr66:
		{
			#line 56 "httpclient_parser.rl"
			MARK(field_start, p); }
		
		goto st90;
		st90:
		p+= 1;
		if ( p == pe )
		goto _test_eof90;
		st_case_90:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 76: {
				goto st91;
			}
			case 79: {
				goto st26;
			}
			case 108: {
				goto st91;
			}
			case 111: {
				goto st26;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st91:
		p+= 1;
		if ( p == pe )
		goto _test_eof91;
		st_case_91:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 79: {
				goto st92;
			}
			case 111: {
				goto st92;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st92:
		p+= 1;
		if ( p == pe )
		goto _test_eof92;
		st_case_92:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 83: {
				goto st93;
			}
			case 115: {
				goto st93;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st93:
		p+= 1;
		if ( p == pe )
		goto _test_eof93;
		st_case_93:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 69: {
				goto st94;
			}
			case 101: {
				goto st94;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st94:
		p+= 1;
		if ( p == pe )
		goto _test_eof94;
		st_case_94:
		switch( ( (*( p))) ) {
			case 10: {
				goto st43;
			}
			case 13: {
				goto st88;
			}
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		ctr61:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st95;
		st95:
		p+= 1;
		if ( p == pe )
		goto _test_eof95;
		st_case_95:
		switch( ( (*( p))) ) {
			case 10: {
				goto st36;
			}
			case 32: {
				goto st37;
			}
			case 67: {
				goto st38;
			}
			case 99: {
				goto st38;
			}
		}
		if ( 9 <= ( (*( p))) && ( (*( p))) <= 13 ) {
			goto st37;
		}
		{
			goto st0;
		}
		ctr62:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		
		goto st96;
		st96:
		p+= 1;
		if ( p == pe )
		goto _test_eof96;
		st_case_96:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr45;
			}
			case 13: {
				goto ctr46;
			}
			case 76: {
				goto st97;
			}
			case 108: {
				goto st97;
			}
		}
		{
			goto st23;
		}
		st97:
		p+= 1;
		if ( p == pe )
		goto _test_eof97;
		st_case_97:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr45;
			}
			case 13: {
				goto ctr46;
			}
			case 79: {
				goto st98;
			}
			case 111: {
				goto st98;
			}
		}
		{
			goto st23;
		}
		st98:
		p+= 1;
		if ( p == pe )
		goto _test_eof98;
		st_case_98:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr45;
			}
			case 13: {
				goto ctr46;
			}
			case 83: {
				goto st99;
			}
			case 115: {
				goto st99;
			}
		}
		{
			goto st23;
		}
		st99:
		p+= 1;
		if ( p == pe )
		goto _test_eof99;
		st_case_99:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr45;
			}
			case 13: {
				goto ctr46;
			}
			case 69: {
				goto st100;
			}
			case 101: {
				goto st100;
			}
		}
		{
			goto st23;
		}
		st100:
		p+= 1;
		if ( p == pe )
		goto _test_eof100;
		st_case_100:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr136;
			}
			case 13: {
				goto ctr137;
			}
		}
		{
			goto st23;
		}
		st101:
		p+= 1;
		if ( p == pe )
		goto _test_eof101;
		st_case_101:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 69: {
				goto st102;
			}
			case 101: {
				goto st102;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st102:
		p+= 1;
		if ( p == pe )
		goto _test_eof102;
		st_case_102:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 78: {
				goto st103;
			}
			case 110: {
				goto st103;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st103:
		p+= 1;
		if ( p == pe )
		goto _test_eof103;
		st_case_103:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 84: {
				goto st104;
			}
			case 116: {
				goto st104;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st104:
		p+= 1;
		if ( p == pe )
		goto _test_eof104;
		st_case_104:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 45: {
				goto st105;
			}
			case 46: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 48 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 57 ) {
			if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 65 ) {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st105:
		p+= 1;
		if ( p == pe )
		goto _test_eof105;
		st_case_105:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 76: {
				goto st106;
			}
			case 108: {
				goto st106;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st106:
		p+= 1;
		if ( p == pe )
		goto _test_eof106;
		st_case_106:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 69: {
				goto st107;
			}
			case 101: {
				goto st107;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st107:
		p+= 1;
		if ( p == pe )
		goto _test_eof107;
		st_case_107:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 78: {
				goto st108;
			}
			case 110: {
				goto st108;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st108:
		p+= 1;
		if ( p == pe )
		goto _test_eof108;
		st_case_108:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 71: {
				goto st109;
			}
			case 103: {
				goto st109;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st109:
		p+= 1;
		if ( p == pe )
		goto _test_eof109;
		st_case_109:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 84: {
				goto st110;
			}
			case 116: {
				goto st110;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st110:
		p+= 1;
		if ( p == pe )
		goto _test_eof110;
		st_case_110:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 72: {
				goto st111;
			}
			case 104: {
				goto st111;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		st111:
		p+= 1;
		if ( p == pe )
		goto _test_eof111;
		st_case_111:
		switch( ( (*( p))) ) {
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr148;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st21;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		ctr149:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		
		goto st112;
		ctr148:
		{
			#line 58 "httpclient_parser.rl"
			
			parser->field_len = LEN(field_start, p);
		}
		
		goto st112;
		st112:
		p+= 1;
		if ( p == pe )
		goto _test_eof112;
		st_case_112:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr150;
			}
			case 13: {
				goto ctr151;
			}
			case 32: {
				goto ctr149;
			}
		}
		if ( ( (*( p))) > 12 ) {
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto ctr152;
			}
		} else if ( ( (*( p))) >= 9 ) {
			goto ctr149;
		}
		{
			goto ctr40;
		}
		ctr150:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st113;
		st113:
		p+= 1;
		if ( p == pe )
		goto _test_eof113;
		st_case_113:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr154;
			}
			case 13: {
				goto st116;
			}
			case 32: {
				goto st114;
			}
			case 33: {
				goto ctr35;
			}
			case 67: {
				goto ctr36;
			}
			case 84: {
				goto ctr37;
			}
			case 99: {
				goto ctr36;
			}
			case 116: {
				goto ctr37;
			}
			case 124: {
				goto ctr35;
			}
			case 126: {
				goto ctr35;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) < 35 ) {
				if ( 9 <= ( (*( p))) && ( (*( p))) <= 12 ) {
					goto st114;
				}
			} else if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto ctr35;
				}
			} else {
				goto ctr35;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto ctr156;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto ctr35;
				}
			} else {
				goto ctr35;
			}
		} else {
			goto ctr35;
		}
		{
			goto st0;
		}
		st114:
		p+= 1;
		if ( p == pe )
		goto _test_eof114;
		st_case_114:
		if ( ( (*( p))) == 32 ) {
			goto st114;
		}
		if ( ( (*( p))) > 13 ) {
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto ctr157;
			}
		} else if ( ( (*( p))) >= 9 ) {
			goto st114;
		}
		{
			goto st0;
		}
		ctr157:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		
		goto st115;
		st115:
		p+= 1;
		if ( p == pe )
		goto _test_eof115;
		st_case_115:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr158;
			}
			case 13: {
				goto ctr159;
			}
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto st115;
		}
		{
			goto st0;
		}
		ctr154:
		{
			#line 111 "httpclient_parser.rl"
			
			parser->body_start = p - buffer + 1; 
			if(parser->header_done != NULL)
			parser->header_done(parser->data, p + 1, pe - p - 1);
			{p+= 1; cs = 123; goto _out;}
		}
		
		goto st123;
		st123:
		p+= 1;
		if ( p == pe )
		goto _test_eof123;
		st_case_123:
		if ( ( (*( p))) == 32 ) {
			goto st114;
		}
		if ( ( (*( p))) > 13 ) {
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto ctr157;
			}
		} else if ( ( (*( p))) >= 9 ) {
			goto st114;
		}
		{
			goto st0;
		}
		st116:
		p+= 1;
		if ( p == pe )
		goto _test_eof116;
		st_case_116:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr154;
			}
			case 32: {
				goto st114;
			}
		}
		if ( ( (*( p))) > 13 ) {
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto ctr157;
			}
		} else if ( ( (*( p))) >= 9 ) {
			goto st114;
		}
		{
			goto st0;
		}
		ctr156:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		{
			#line 56 "httpclient_parser.rl"
			MARK(field_start, p); }
		
		goto st117;
		st117:
		p+= 1;
		if ( p == pe )
		goto _test_eof117;
		st_case_117:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr158;
			}
			case 13: {
				goto ctr159;
			}
			case 33: {
				goto st21;
			}
			case 58: {
				goto ctr39;
			}
			case 124: {
				goto st21;
			}
			case 126: {
				goto st21;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto st21;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto st21;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto st117;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto st21;
				}
			} else {
				goto st21;
			}
		} else {
			goto st21;
		}
		{
			goto st0;
		}
		ctr151:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		{
			#line 72 "httpclient_parser.rl"
			
			if(parser->http_field != NULL) {
				parser->http_field(parser->data, PTR_TO(field_start), parser->field_len, PTR_TO(mark), LEN(mark, p));
			}
		}
		
		goto st118;
		st118:
		p+= 1;
		if ( p == pe )
		goto _test_eof118;
		st_case_118:
		switch( ( (*( p))) ) {
			case 10: {
				goto st113;
			}
			case 32: {
				goto st114;
			}
		}
		if ( ( (*( p))) > 13 ) {
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto ctr157;
			}
		} else if ( ( (*( p))) >= 9 ) {
			goto st114;
		}
		{
			goto st0;
		}
		ctr152:
		{
			#line 62 "httpclient_parser.rl"
			MARK(mark, p); }
		
		goto st119;
		st119:
		p+= 1;
		if ( p == pe )
		goto _test_eof119;
		st_case_119:
		switch( ( (*( p))) ) {
			case 10: {
				goto ctr158;
			}
			case 13: {
				goto ctr159;
			}
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto st119;
		}
		{
			goto st23;
		}
		st_out:
		_test_eof2: cs = 2; goto _test_eof; 
		_test_eof120: cs = 120; goto _test_eof; 
		_test_eof3: cs = 3; goto _test_eof; 
		_test_eof4: cs = 4; goto _test_eof; 
		_test_eof5: cs = 5; goto _test_eof; 
		_test_eof6: cs = 6; goto _test_eof; 
		_test_eof7: cs = 7; goto _test_eof; 
		_test_eof8: cs = 8; goto _test_eof; 
		_test_eof9: cs = 9; goto _test_eof; 
		_test_eof10: cs = 10; goto _test_eof; 
		_test_eof11: cs = 11; goto _test_eof; 
		_test_eof12: cs = 12; goto _test_eof; 
		_test_eof13: cs = 13; goto _test_eof; 
		_test_eof14: cs = 14; goto _test_eof; 
		_test_eof15: cs = 15; goto _test_eof; 
		_test_eof16: cs = 16; goto _test_eof; 
		_test_eof17: cs = 17; goto _test_eof; 
		_test_eof18: cs = 18; goto _test_eof; 
		_test_eof19: cs = 19; goto _test_eof; 
		_test_eof20: cs = 20; goto _test_eof; 
		_test_eof21: cs = 21; goto _test_eof; 
		_test_eof22: cs = 22; goto _test_eof; 
		_test_eof23: cs = 23; goto _test_eof; 
		_test_eof24: cs = 24; goto _test_eof; 
		_test_eof25: cs = 25; goto _test_eof; 
		_test_eof26: cs = 26; goto _test_eof; 
		_test_eof27: cs = 27; goto _test_eof; 
		_test_eof28: cs = 28; goto _test_eof; 
		_test_eof29: cs = 29; goto _test_eof; 
		_test_eof30: cs = 30; goto _test_eof; 
		_test_eof31: cs = 31; goto _test_eof; 
		_test_eof32: cs = 32; goto _test_eof; 
		_test_eof33: cs = 33; goto _test_eof; 
		_test_eof34: cs = 34; goto _test_eof; 
		_test_eof35: cs = 35; goto _test_eof; 
		_test_eof36: cs = 36; goto _test_eof; 
		_test_eof37: cs = 37; goto _test_eof; 
		_test_eof38: cs = 38; goto _test_eof; 
		_test_eof39: cs = 39; goto _test_eof; 
		_test_eof40: cs = 40; goto _test_eof; 
		_test_eof41: cs = 41; goto _test_eof; 
		_test_eof42: cs = 42; goto _test_eof; 
		_test_eof43: cs = 43; goto _test_eof; 
		_test_eof44: cs = 44; goto _test_eof; 
		_test_eof45: cs = 45; goto _test_eof; 
		_test_eof46: cs = 46; goto _test_eof; 
		_test_eof47: cs = 47; goto _test_eof; 
		_test_eof48: cs = 48; goto _test_eof; 
		_test_eof49: cs = 49; goto _test_eof; 
		_test_eof50: cs = 50; goto _test_eof; 
		_test_eof51: cs = 51; goto _test_eof; 
		_test_eof52: cs = 52; goto _test_eof; 
		_test_eof53: cs = 53; goto _test_eof; 
		_test_eof54: cs = 54; goto _test_eof; 
		_test_eof55: cs = 55; goto _test_eof; 
		_test_eof56: cs = 56; goto _test_eof; 
		_test_eof57: cs = 57; goto _test_eof; 
		_test_eof58: cs = 58; goto _test_eof; 
		_test_eof59: cs = 59; goto _test_eof; 
		_test_eof60: cs = 60; goto _test_eof; 
		_test_eof61: cs = 61; goto _test_eof; 
		_test_eof62: cs = 62; goto _test_eof; 
		_test_eof63: cs = 63; goto _test_eof; 
		_test_eof64: cs = 64; goto _test_eof; 
		_test_eof65: cs = 65; goto _test_eof; 
		_test_eof66: cs = 66; goto _test_eof; 
		_test_eof67: cs = 67; goto _test_eof; 
		_test_eof68: cs = 68; goto _test_eof; 
		_test_eof69: cs = 69; goto _test_eof; 
		_test_eof70: cs = 70; goto _test_eof; 
		_test_eof71: cs = 71; goto _test_eof; 
		_test_eof121: cs = 121; goto _test_eof; 
		_test_eof72: cs = 72; goto _test_eof; 
		_test_eof73: cs = 73; goto _test_eof; 
		_test_eof74: cs = 74; goto _test_eof; 
		_test_eof75: cs = 75; goto _test_eof; 
		_test_eof76: cs = 76; goto _test_eof; 
		_test_eof77: cs = 77; goto _test_eof; 
		_test_eof78: cs = 78; goto _test_eof; 
		_test_eof79: cs = 79; goto _test_eof; 
		_test_eof80: cs = 80; goto _test_eof; 
		_test_eof81: cs = 81; goto _test_eof; 
		_test_eof82: cs = 82; goto _test_eof; 
		_test_eof83: cs = 83; goto _test_eof; 
		_test_eof84: cs = 84; goto _test_eof; 
		_test_eof85: cs = 85; goto _test_eof; 
		_test_eof86: cs = 86; goto _test_eof; 
		_test_eof87: cs = 87; goto _test_eof; 
		_test_eof88: cs = 88; goto _test_eof; 
		_test_eof122: cs = 122; goto _test_eof; 
		_test_eof89: cs = 89; goto _test_eof; 
		_test_eof90: cs = 90; goto _test_eof; 
		_test_eof91: cs = 91; goto _test_eof; 
		_test_eof92: cs = 92; goto _test_eof; 
		_test_eof93: cs = 93; goto _test_eof; 
		_test_eof94: cs = 94; goto _test_eof; 
		_test_eof95: cs = 95; goto _test_eof; 
		_test_eof96: cs = 96; goto _test_eof; 
		_test_eof97: cs = 97; goto _test_eof; 
		_test_eof98: cs = 98; goto _test_eof; 
		_test_eof99: cs = 99; goto _test_eof; 
		_test_eof100: cs = 100; goto _test_eof; 
		_test_eof101: cs = 101; goto _test_eof; 
		_test_eof102: cs = 102; goto _test_eof; 
		_test_eof103: cs = 103; goto _test_eof; 
		_test_eof104: cs = 104; goto _test_eof; 
		_test_eof105: cs = 105; goto _test_eof; 
		_test_eof106: cs = 106; goto _test_eof; 
		_test_eof107: cs = 107; goto _test_eof; 
		_test_eof108: cs = 108; goto _test_eof; 
		_test_eof109: cs = 109; goto _test_eof; 
		_test_eof110: cs = 110; goto _test_eof; 
		_test_eof111: cs = 111; goto _test_eof; 
		_test_eof112: cs = 112; goto _test_eof; 
		_test_eof113: cs = 113; goto _test_eof; 
		_test_eof114: cs = 114; goto _test_eof; 
		_test_eof115: cs = 115; goto _test_eof; 
		_test_eof123: cs = 123; goto _test_eof; 
		_test_eof116: cs = 116; goto _test_eof; 
		_test_eof117: cs = 117; goto _test_eof; 
		_test_eof118: cs = 118; goto _test_eof; 
		_test_eof119: cs = 119; goto _test_eof; 
		
		_test_eof: {}
		_out: {}
	}
	
	#line 203 "httpclient_parser.rl"
	
	
	parser->cs = cs;
	parser->nread += p - (buffer + off);
	
	assert(p <= pe && "buffer overflow after parsing execute");
	assert(parser->nread <= len && "nread longer than length");
	assert(parser->body_start <= len && "body starts after buffer end");
	check(parser->mark < len, "mark is after buffer end");
	check(parser->field_len <= len, "field has length longer than whole buffer");
	check(parser->field_start < len, "field starts after buffer end");
	
	//if(parser->body_start) {
		//    /* final \r\n combo encountered so stop right here */
		//    parser->nread++;
		//}
	
	return(parser->nread);
	
	error:
	return -1;
}

int httpclient_parser_finish(httpclient_parser *parser)
{
	int cs = parser->cs;
	
	parser->cs = cs;
	
	if (httpclient_parser_has_error(parser) ) {
		return -1;
	} else if (httpclient_parser_is_finished(parser) ) {
		return 1;
	} else {
		return 0;
	}
}

int httpclient_parser_has_error(httpclient_parser *parser) {
	return parser->cs == httpclient_parser_error;
}

int httpclient_parser_is_finished(httpclient_parser *parser) {
	return parser->cs == httpclient_parser_first_final;
}

