# Sistema de Gestão de Consultas Médicas 🏥

## 📌 Sobre o Projeto
Este é um sistema simples de gestão de consultas médicas desenvolvido em C. Ele permite o cadastro de usuários e consultas, além de oferecer funcionalidades como listagem, edição, exclusão e filtragem de consultas por tipo e data.

## 🚀 Funcionalidades
- Cadastro de usuários com autenticação por nome e senha.
- Cadastro, listagem, edição e exclusão de consultas.
- Filtros para visualizar consultas por tipo ou data.
- Busca de ficha do paciente pelo nome.
- Seleção de médicos com base na especialidade.

## 🛠️ Tecnologias Utilizadas
- Linguagem de programação C.
- Biblioteca padrão do C (`stdio.h`, `stdlib.h`, `string.h`, `locale.h`).

## 📦 Como Compilar e Executar
1. **Compilar o código**:
   ```bash
   gcc sistema_medico.c -o sistema_medico
   ```
2. **Executar o programa**:
   ```bash
   ./sistema_medico
   ```

## 📌 Como Usar
1. Ao iniciar o sistema, você pode:
   - Criar um novo usuário.
   - Fazer login com um usuário cadastrado.
2. Após o login, você pode:
   - Agendar consultas.
   - Listar consultas existentes.
   - Editar ou excluir consultas.
   - Filtrar consultas por tipo ou data.
   - Buscar pacientes pelo nome.

## 📄 Estrutura do Código
- `Usuario`: Estrutura para armazenar os dados do usuário.
- `Consulta`: Estrutura para armazenar os dados das consultas.
- **Funções principais**:
  - `cadastrar_usuario()`
  - `realizar_login()`
  - `cadastrar_consulta()`
  - `listar_consultas()`
  - `editar_consulta()`
  - `excluir_consulta()`
  - `filtrar_consultas_por_tipo()`
  - `filtrar_consultas_por_dia()`


