#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen/backend.h"
#include "codegen/tac.h"

// Estrutura para armazenar instruções de máquina
typedef struct {
    char* codigo;
    struct MachineInstr* next;
} MachineInstr;

// Cabeça da lista de instruções de máquina
static MachineInstr* codigo_maquina = NULL;

// Flag para indicar se o backend foi inicializado
static int backend_inicializado = 0;

// Armazena o nome do arquivo temporário para o código assembly
static char* temp_asm_file = NULL;

/**
 * Adiciona uma instrução de máquina à lista
 */
static void adiciona_instrucao(const char* instr) {
    MachineInstr* nova = (MachineInstr*)malloc(sizeof(MachineInstr));
    if (!nova) {
        fprintf(stderr, "Erro: falha na alocação de memória para instrução de máquina\n");
        exit(1);
    }
    
    nova->codigo = strdup(instr);
    nova->next = NULL;
    
    // Adiciona ao final da lista
    if (codigo_maquina == NULL) {
        codigo_maquina = nova;
    } else {
        MachineInstr* atual = codigo_maquina;
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = nova;
    }
}

/**
 * Inicializa o gerador de código de máquina
 */
void inicializa_backend() {
    if (backend_inicializado) {
        return;
    }
    
    codigo_maquina = NULL;
    backend_inicializado = 1;
    
    // Adiciona o prólogo do programa
    adiciona_instrucao(".section .text");
    adiciona_instrucao(".globl main");
    adiciona_instrucao("");
}

/**
 * Converte uma instrução TAC em código assembly x86
 */
static void traduz_instrucao_tac(TacInstr* instr) {
    char buffer[256];
    
    switch (instr->op) {
        case TAC_ADD:
            sprintf(buffer, "    # %s = %s + %s", 
                    tac_addr_to_string(instr->dest), 
                    tac_addr_to_string(instr->src1), 
                    tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    addl %s, %%eax", tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %%eax, %s", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            break;
            
        case TAC_SUB:
            sprintf(buffer, "    # %s = %s - %s", 
                    tac_addr_to_string(instr->dest), 
                    tac_addr_to_string(instr->src1), 
                    tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    subl %s, %%eax", tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %%eax, %s", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            break;
            
        case TAC_MUL:
            sprintf(buffer, "    # %s = %s * %s", 
                    tac_addr_to_string(instr->dest), 
                    tac_addr_to_string(instr->src1), 
                    tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    imull %s, %%eax", tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %%eax, %s", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            break;
            
        case TAC_DIV:
            sprintf(buffer, "    # %s = %s / %s", 
                    tac_addr_to_string(instr->dest), 
                    tac_addr_to_string(instr->src1), 
                    tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            adiciona_instrucao("    cdq");  // Estende o sinal para EDX:EAX
            sprintf(buffer, "    idivl %s", tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %%eax, %s", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            break;
            
        case TAC_MOD:
            sprintf(buffer, "    # %s = %s %% %s", 
                    tac_addr_to_string(instr->dest), 
                    tac_addr_to_string(instr->src1), 
                    tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            adiciona_instrucao("    cdq");  // Estende o sinal para EDX:EAX
            sprintf(buffer, "    idivl %s", tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %%edx, %s", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            break;
            
        case TAC_ASSIGN:
            sprintf(buffer, "    # %s = %s", 
                    tac_addr_to_string(instr->dest), 
                    tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %%eax, %s", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            break;
            
        case TAC_LABEL:
            sprintf(buffer, "%s:", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            break;
            
        case TAC_JUMP:
            sprintf(buffer, "    # goto %s", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    jmp %s", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            break;
            
        case TAC_IF:
            sprintf(buffer, "    # if %s goto %s", 
                    tac_addr_to_string(instr->src1), 
                    tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            adiciona_instrucao("    cmpl $0, %eax");
            sprintf(buffer, "    jne %s", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            break;
            
        case TAC_IFZ:
            sprintf(buffer, "    # if %s == 0 goto %s", 
                    tac_addr_to_string(instr->src1), 
                    tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            adiciona_instrucao("    cmpl $0, %eax");
            sprintf(buffer, "    je %s", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            break;
            
        case TAC_EQ:
            sprintf(buffer, "    # %s = (%s == %s)", 
                    tac_addr_to_string(instr->dest), 
                    tac_addr_to_string(instr->src1), 
                    tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    cmpl %s, %%eax", tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            adiciona_instrucao("    sete %al");
            adiciona_instrucao("    movzbl %al, %eax");  // Zero-extend byte to dword
            sprintf(buffer, "    movl %%eax, %s", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            break;
            
        case TAC_NE:
            sprintf(buffer, "    # %s = (%s != %s)", 
                    tac_addr_to_string(instr->dest), 
                    tac_addr_to_string(instr->src1), 
                    tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    cmpl %s, %%eax", tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            adiciona_instrucao("    setne %al");
            adiciona_instrucao("    movzbl %al, %eax");
            sprintf(buffer, "    movl %%eax, %s", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            break;
            
        case TAC_LT:
            sprintf(buffer, "    # %s = (%s < %s)", 
                    tac_addr_to_string(instr->dest), 
                    tac_addr_to_string(instr->src1), 
                    tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    cmpl %s, %%eax", tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            adiciona_instrucao("    setl %al");
            adiciona_instrucao("    movzbl %al, %eax");
            sprintf(buffer, "    movl %%eax, %s", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            break;
            
        case TAC_GT:
            sprintf(buffer, "    # %s = (%s > %s)", 
                    tac_addr_to_string(instr->dest), 
                    tac_addr_to_string(instr->src1), 
                    tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    cmpl %s, %%eax", tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            adiciona_instrucao("    setg %al");
            adiciona_instrucao("    movzbl %al, %eax");
            sprintf(buffer, "    movl %%eax, %s", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            break;
            
        case TAC_LE:
            sprintf(buffer, "    # %s = (%s <= %s)", 
                    tac_addr_to_string(instr->dest), 
                    tac_addr_to_string(instr->src1), 
                    tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    cmpl %s, %%eax", tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            adiciona_instrucao("    setle %al");
            adiciona_instrucao("    movzbl %al, %eax");
            sprintf(buffer, "    movl %%eax, %s", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            break;
            
        case TAC_GE:
            sprintf(buffer, "    # %s = (%s >= %s)", 
                    tac_addr_to_string(instr->dest), 
                    tac_addr_to_string(instr->src1), 
                    tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    cmpl %s, %%eax", tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            adiciona_instrucao("    setge %al");
            adiciona_instrucao("    movzbl %al, %eax");
            sprintf(buffer, "    movl %%eax, %s", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            break;
            
        case TAC_RETURN:
            sprintf(buffer, "    # return %s", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            adiciona_instrucao("    leave");
            adiciona_instrucao("    ret");
            break;
            
        case TAC_ARRAY_STORE:
            sprintf(buffer, "    # %s[%s] = %s", 
                    tac_addr_to_string(instr->dest), 
                    tac_addr_to_string(instr->src1), 
                    tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            adiciona_instrucao("    imull $4, %eax");  // Assume 4 bytes per element
            sprintf(buffer, "    leal %s(,%%eax,1), %%edx", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            adiciona_instrucao("    movl %eax, (%edx)");
            break;
            
        case TAC_ARRAY_LOAD:
            sprintf(buffer, "    # %s = %s[%s]", 
                    tac_addr_to_string(instr->dest), 
                    tac_addr_to_string(instr->src1), 
                    tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            sprintf(buffer, "    movl %s, %%eax", tac_addr_to_string(instr->src2));
            adiciona_instrucao(buffer);
            adiciona_instrucao("    imull $4, %eax");  // Assume 4 bytes per element
            sprintf(buffer, "    leal %s(,%%eax,1), %%edx", tac_addr_to_string(instr->src1));
            adiciona_instrucao(buffer);
            adiciona_instrucao("    movl (%edx), %eax");
            sprintf(buffer, "    movl %%eax, %s", tac_addr_to_string(instr->dest));
            adiciona_instrucao(buffer);
            break;
            
        default:
            sprintf(buffer, "    # Operação TAC não implementada: %d", instr->op);
            adiciona_instrucao(buffer);
            break;
    }
    
    adiciona_instrucao("");  // Linha em branco após cada instrução para melhor legibilidade
}

/**
 * Adiciona o prólogo e epílogo para a função main
 */
static void adiciona_main_frame() {
    adiciona_instrucao("main:");
    adiciona_instrucao("    pushl %ebp");
    adiciona_instrucao("    movl %esp, %ebp");
    adiciona_instrucao("    subl $1000, %esp");  // Aloca espaço para variáveis locais (ajustar conforme necessário)
    adiciona_instrucao("");
    
    // O epílogo será adicionado ao final, ou pelo comando TAC_RETURN
}

/**
 * Gera código de máquina a partir do código intermediário TAC
 * @return 0 em caso de sucesso, código de erro caso contrário
 */
int gera_codigo_maquina() {
    if (!backend_inicializado) {
        inicializa_backend();
    }
    
    // Obtém a lista de instruções TAC
    TacInstr* instr = tac_first_instr();
    
    if (!instr) {
        fprintf(stderr, "Aviso: nenhuma instrução TAC para traduzir\n");
        return 1;
    }
    
    // Adiciona o prólogo para a função main
    adiciona_main_frame();
    
    // Traduz cada instrução TAC para código de máquina
    while (instr) {
        traduz_instrucao_tac(instr);
        instr = instr->next;
    }
    
    return 0;
}

/**
 * Imprime o código de máquina gerado
 * @param output Arquivo de saída (se NULL, usa stdout)
 */
void imprime_codigo_maquina(FILE* output) {
    if (!output) {
        output = stdout;
    }
    
    MachineInstr* instr = codigo_maquina;
    fprintf(output, ";;; Código Assembly x86 gerado ;;;\n\n");
    
    while (instr) {
        fprintf(output, "%s\n", instr->codigo);
        instr = instr->next;
    }
}

/**
 * Salva o código de máquina em um arquivo
 * @param filename Nome do arquivo de saída
 * @return 0 em caso de sucesso, código de erro caso contrário
 */
int salva_codigo_maquina(const char* filename) {
    char assembly_filename[256];
    char comando[512];
    
    // Cria um nome para o arquivo assembly
    sprintf(assembly_filename, "%s.s", filename);
    
    // Salva o código assembly
    FILE* output = fopen(assembly_filename, "w");
    if (!output) {
        fprintf(stderr, "Erro: não foi possível criar o arquivo assembly '%s'\n", assembly_filename);
        return 1;
    }
    
    imprime_codigo_maquina(output);
    fclose(output);
    
    // Armazena o nome do arquivo temporário para limpeza posterior
    if (temp_asm_file) {
        free(temp_asm_file);
    }
    temp_asm_file = strdup(assembly_filename);
    
    // Usa GCC para compilar o assembly para um executável
    sprintf(comando, "gcc -m32 -o %s %s", filename, assembly_filename);
    int resultado = system(comando);
    
    if (resultado != 0) {
        fprintf(stderr, "Erro: falha ao compilar o código assembly para o executável '%s'\n", filename);
        return 1;
    }
    
    printf("Arquivo executável '%s' gerado com sucesso.\n", filename);
    return 0;
}

/**
 * Libera os recursos utilizados pelo gerador de código de máquina
 */
void finaliza_backend() {
    // Libera a lista de instruções de máquina
    MachineInstr* instr = codigo_maquina;
    while (instr) {
        MachineInstr* tmp = instr;
        instr = instr->next;
        free(tmp->codigo);
        free(tmp);
    }
    
    // Remove o arquivo assembly temporário
    if (temp_asm_file) {
        remove(temp_asm_file);
        free(temp_asm_file);
        temp_asm_file = NULL;
    }
    
    codigo_maquina = NULL;
    backend_inicializado = 0;
}
