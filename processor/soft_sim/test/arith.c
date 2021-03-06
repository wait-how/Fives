/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "arith.src" instead.
 */

#include <check.h>

#line 1 "arith.src"
#include "test.h"
	

#line 5
// lots of identical code here, should really clean this up
// no isolation argument because check already does that

// lots of repetetive code here but honestly I'm tired of figuring out test case forking
// not freeing memory here because I don't care


START_TEST(add_basic1)
{
#line 14
	SETUP_M();

	p->i.f_d = R3;
	
	instr_add(p);
	
	ck_assert_int_eq(p->regfile[R3], 3);

}
END_TEST

START_TEST(add_basic2)
{
#line 23
	SETUP_M();

	p->regfile[R1] = 44;
	p->regfile[R2] = 32;

	instr_add(p);
	
	ck_assert_int_eq(p->regfile[R3], 76);
	
	free(p);
	
}
END_TEST

START_TEST(add_byte)
{
#line 35
	SETUP_M();
	
	p->regfile[R3] = 0xFFFF;
	p->regfile[R1] = 0x00FF;
	p->regfile[R2] = 0x00A4;
	
	instr_add(p);
	ck_assert_int_eq(p->regfile[R3], 0xFFA3);

}
END_TEST

START_TEST(add_immediate)
{
#line 45
	SETUP_M();

	p->i.f_pm = 0b100;
	p->i.f2_s = R1;
	p->i.f2_short_imm = 20;

	instr_add(p);
	ck_assert_int_eq(p->regfile[R3], 21);

}
END_TEST

START_TEST(add_word)
{
#line 55
	SETUP_M();

	p->i.f_pm = 0b010;
	p->regfile[R1] = 0xFFA0;
	p->regfile[R2] = 45;

	instr_add(p);
	
	ck_assert_int_eq(p->regfile[R3], 0xFFCD);

}
END_TEST

START_TEST(add_dest_r0)
{
#line 66
	SETUP_M();

	p->i.f_d = R0;
	p->i.f_opcode = ADD;

	int err = disp(p, NULL); // not executing an instruction that needs RAM,
							 // so no RAM is provided
	
	ck_assert_int_eq(p->regfile[R0], 0); // check for non-zero R0
	ck_assert_int_eq(err, 0); // no error should be reported for R0 write

}
END_TEST

START_TEST(add_check_byte)
{
#line 78
	SETUP_M();

	// check if the data in byte_regfile matches regfile
	p->regfile[R1] = 0xAAFF;
	
	ck_assert_int_eq(p->byte_regfile[R1*2], 0xFF);
	ck_assert_int_eq(p->byte_regfile[(R1*2)+1], 0xAA);

}
END_TEST

START_TEST(add_signed)
{
#line 87
	SETUP_M();
	
	p->regfile[R1] = (uint16_t) -32767;
	p->regfile[R2] = 10;
	p->i.f_pm = 0b011;
	
	instr_add(p);
	
	ck_assert_int_eq(p->regfile[R3], (uint16_t) -32757);

}
END_TEST

START_TEST(sub)
{
#line 100
	SETUP_M();
	
	instr_sub(p);
	ck_assert_int_eq(p->regfile[R3], 1);

}
END_TEST

START_TEST(sub_signed)
{
#line 106
	SETUP_M();
	
	

}
END_TEST

START_TEST(mul_basic1)
{
#line 113
	SETUP_M();

	p->i.g_s0 = R6;
	p->i.g_s1 = R6;
	
	p->i.g_l = R3;
	p->i.g_h = R4;
	
	instr_mul(p);
	
	ck_assert_int_eq(p->regfile[R3], 36);
	ck_assert_int_eq(p->regfile[R4], 4); // shouldn't be modified

}
END_TEST

START_TEST(mul_signed)
{
#line 127
	SETUP_M();

	p->regfile[R5] = 0xFFFF;

	p->i.g_s0 = R6;
	p->i.g_s1 = R5;

	p->i.g_l = R3;
	p->i.g_h = R4;
	
	p->i.f_pm = 0b011;
	
	instr_mul(p);

	ck_assert_int_eq(p->regfile[R3], (uint16_t) -6);
	ck_assert_int_eq(p->regfile[R4], 4);
}
END_TEST

START_TEST(ash_basic1)
{
#line 146
	SETUP_M();

	p->regfile[R2] = 0xAAFF;
	p->i.f_pm = 0b010; // word shift, right, using reg
	
	instr_lsh(p);
	
	ck_assert_int_eq(p->regfile[R3], 0x557F);

}
END_TEST

START_TEST(sex_basic1)
{
#line 158
	SETUP_M();
	
	p->regfile[R1] = (int8_t) -1;
	ck_assert_int_eq((int8_t) p->byte_regfile[R1+1], -1);
	instr_sex(p);
	ck_assert_int_eq((int16_t) p->regfile[R1], -1);
	
	
}
END_TEST

int main(void)
{
    Suite *s1 = suite_create("arith-check");
    TCase *tc1_1 = tcase_create("add_instr");
    TCase *tc1_2 = tcase_create("sub_instr");
    TCase *tc1_3 = tcase_create("mul_instr");
    TCase *tc1_4 = tcase_create("shift_instr");
    TCase *tc1_5 = tcase_create("sign_extend_instr");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, add_basic1);
    tcase_add_test(tc1_1, add_basic2);
    tcase_add_test(tc1_1, add_byte);
    tcase_add_test(tc1_1, add_immediate);
    tcase_add_test(tc1_1, add_word);
    tcase_add_test(tc1_1, add_dest_r0);
    tcase_add_test(tc1_1, add_check_byte);
    tcase_add_test(tc1_1, add_signed);
    suite_add_tcase(s1, tc1_2);
    tcase_add_test(tc1_2, sub);
    tcase_add_test(tc1_2, sub_signed);
    suite_add_tcase(s1, tc1_3);
    tcase_add_test(tc1_3, mul_basic1);
    tcase_add_test(tc1_3, mul_signed);
    suite_add_tcase(s1, tc1_4);
    tcase_add_test(tc1_4, ash_basic1);
    suite_add_tcase(s1, tc1_5);
    tcase_add_test(tc1_5, sex_basic1);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
