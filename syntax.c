#include "syntax.h"

const char *reg_16[] = {
    "sp",
    "bc",
    "de",
    "hl",
    "pc",
};

const char *reg_8[] = {
    "a",
    "b",
    "c",
    "d",
    "e",
    "h",
    "l",
};

const char *no_operand_instructions[] = {
    "NOP",
    "RLC",
    "RRC",
    "RAL",
    "RAR",
    "RIM",
    "DAA",
    "CMA",
    "SIM",
    "STC",
    "CMC",
    "HLT",
    "RNZ",
    "RZ",
    "RET",
    "RNC",
    "RC",
    "RPO",
    "XTHL",
    "RPE",
    "PCHL",
    "XCHG",
    "RP",
    "DI",
    "RM",
    "SPHL",
    "EI",
};

const char*single_operand_instructions[] = {
    "ADD",
    "ADC"
    "STAX",
    "INX",
    "INR",
    "DCR",
    "DAD",
    "LDAX",
    "DCX",
    "SHLD",
    "LDHD",
    "STA",
    "LDA",
    "SUB",
    "SBB",
    "ANA",
    "XRA",
    "ORA",
    "CMP",
    "POP",
    "JNZ",
    "JMP",
    "CNZ",
    "PUSH",
    "ADI",
    "RST",
    "JZ",
    "CZ",
    "CALL",
    "ACI",
    "JNC",
    "OUT",
    "CNC",
    "SUI",
    "JC",
    "IN",
    "CC",
    "SBI",
    "JPO",
    "CPO",
    "ANI",
    "JPE",
    "CPE",
    "XRI",
    "JP",
    "CP",
    "ORI",
    "JM",
    "CM",
    "CPI",
};

const char*multiple_operand_instructions[] = {
    "LXI",
    "MVI",
    "MOV",

};
static int is_valid(const char **list, int list_size, char *buffer)
{
    int i;

    for (i = 0; i < list_size/ sizeof(char*); i++)
    {
        if (strcmp(list[i], buffer) == 0)
            return 0;
    }
    
    return -1;

}

static int is_8bit_hex(char *buffer)
{
    int i;
    char *tmp = buffer;
    if (*tmp == '0' && (*(tmp + 1) == 'x' || *(tmp + 1) == 'X'))
    {
        i = 0;
        tmp += 2;
        while (*tmp != '\0')
        {
            if (*tmp >= 48 && *tmp <= 57)
            {

            }
            else if (*(tmp) >= 97 && *tmp <= 102)
            {

            }
            else
            {
                printf("Error: `%s' is not hexademical\n", buffer);
                return -1;
            }
            i++;
            tmp++;
        }

        if (i >= 3)
        {
            printf("Error: `%s' is bigger than 8 bit\n", buffer);
            return -1;
        }
    }
    else
    {
        printf("Error: `%s' is not hexademical\n", buffer);
        return -1;
    }
    return 0;
}

static int is_16bit_hex(char *buffer)
{
    int i;
    char *tmp = buffer;
    if (*tmp == '0' && (*(tmp + 1) == 'x' || *(tmp + 1) == 'X'))
    {
        i = 0;
        tmp += 2;
        while (*tmp != '\0')
        {
            if (*tmp >= 48 && *tmp <= 57)
            {

            }
            else if (*(tmp) >= 97 && *tmp <= 102)
            {

            }
            else
            {
                printf("Error: `%s' is not hexademical\n", buffer);
                return -1;
            }
            i++;
            tmp++;
        }

        if (i >= 5)
        {
            printf("Error: `%s' is bigger than 16 bit\n", buffer);
            return -1;
        }
    }
    else
    {
        printf("Error: `%s' is not hexademical\n", buffer);
        return -1;
    }

    return 0;
}

static short verifyMultipleOperandInstruction(char **instruction)
{
    if (strcmp(instruction[0], multiple_operand_instructions[0]) == 0)
    {
        if (is_valid(reg_8, sizeof(reg_8), instruction[1]) != 0)
        {   
            printf("Error: expecting first operand to be 8 bit register\n");
            return -1;
        }
        else
            return is_16bit_hex(instruction[3]);

    }
    else if (strcmp(instruction[0], multiple_operand_instructions[1]) == 0)
    {
        if (is_valid(reg_8, sizeof(reg_8), instruction[1]) != 0)
        {
            printf("Error: expecting first operand to be 8 bit register\n");
            return -1;
        }
        else
            return is_8bit_hex(instruction[3]);
    }
    else if (strcmp(instruction[0], multiple_operand_instructions[2]) == 0)
    {
        if (is_valid(reg_8, sizeof(reg_8), instruction[1]) != 0)
        {
            printf("Error: expecting first operand to be 8 bit register\n");
            return -1;
        }
        if (is_valid(reg_8, sizeof(reg_8), instruction[3]) != 0)
        {
            printf("Error: expecting second operand to be 8 bit register\n");
            return -1;
        }
    }
    return 0;
}

short verifySyntax(char *filename)
{
    char *tmp = NULL;
    char **instructions_tokens = NULL;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return -2;
    
    while (get_line(fp, &tmp) != -1)
    {
        strip_blanks(tmp);
        strip_comments(tmp);
        instructions_tokens = tokenize(tmp);
        if (is_valid(no_operand_instructions, sizeof(no_operand_instructions), instructions_tokens[0]) == 0)
        {
            if (instructions_tokens[1] != NULL)
            {
                printf("%s: Error: Garbage value `%s' after expression `%s'\n", filename, instructions_tokens[1], instructions_tokens[0]);
                return -1;
            }
        }
        else if (is_valid(single_operand_instructions, sizeof(single_operand_instructions), instructions_tokens[0]) == 0)
        {
            if (instructions_tokens[1] == NULL)
            {
                printf("%s: Error: number of operands mismatch for `%s'\n", filename, instructions_tokens[0]);
                return -1;
            }
            if (instructions_tokens[2] != NULL)
            {
                if (strcmp(instructions_tokens[2], ",") == 0)
                {
                    if (instructions_tokens[3] != NULL)
                        printf("%s: Error: Garbage value `%s' after expression `%s'\n", filename, instructions_tokens[3], instructions_tokens[0]);
                    else
                        printf("%s: Error: expecting operand after `%s'\n", filename, instructions_tokens[2]);
                }
            }
        }
        else if (is_valid(multiple_operand_instructions, sizeof(multiple_operand_instructions), instructions_tokens[0]) == 0)
        {
            if (instructions_tokens[1] == NULL || instructions_tokens[2] == NULL)
            {
                printf("%s: Error: number of operands mismatch for `%s'\n", filename, instructions_tokens[0]);
                return -1;
            }
            if (instructions_tokens[3] == NULL)
            {   
                printf("%s: Error: expecting operand after `%s'\n", filename, instructions_tokens[2]);
                return -1;
            }
            
            if (instructions_tokens[4] != NULL)
            {
                printf("%s: Error: Garbage value `%s' after expression `%s'\n", filename, instructions_tokens[3], instructions_tokens[0]);
                return -1;
            }

            verifyMultipleOperandInstruction(instructions_tokens);
        }

        else
        {
            printf("Unknown \"%s\" instruction !\n", instructions_tokens[0]);
        }
    }

    return 0;
    

}

