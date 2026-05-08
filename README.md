# 🖥️ Emulador de Terminal em C (com SDL3)

Este repositório contém o código-fonte de um emulador de terminal customizado construído do zero em **C**. O projeto utiliza a biblioteca **SDL3** para a criação da interface gráfica e chamadas de sistema **POSIX** para o gerenciamento nativo de processos e pseudo-terminais (PTY).

⚠️ **Status:** Projeto em Desenvolvimento (Work in Progress).

## 💡 Sobre o Projeto

O objetivo deste projeto é entender a fundo como terminais de linha de comando funcionam por baixo dos panos. Atualmente, o programa é capaz de:

* Bifurcar um processo (`fork`) e abrir um pseudo-terminal mestre/escravo (`openpty`).
* Executar uma sessão de shell nativa (`/usr/bin/bash`) no processo filho.
* Criar uma janela de renderização gráfica utilizando a biblioteca **SDL3**.
* Capturar eventos de teclado na interface gráfica e enviá-los em tempo real para o processo do shell.
* Ler a saída do shell (modo *non-blocking*) e registrar os dados trafegados.

### 🚧 Limitações Atuais (O que falta implementar)
No momento, a interface gráfica ainda não renderiza o texto (fontes) na tela. A saída gerada pelo bash está sendo capturada pelo buffer e gravada em um arquivo de log chamado `terminal.txt` para fins de depuração. 

**Próximos passos:**
- [ ] Integrar biblioteca de renderização de fontes (ex: `SDL_ttf` ou similar).
- [ ] Mapear e desenhar o buffer de texto na janela do SDL.
- [ ] Implementar um parser para Sequências de Escape ANSI (para suportar cores, movimentação de cursor e limpeza de tela).

---

## ⚙️ Pré-requisitos e Ambiente

Este projeto foi desenhado para rodar em ambientes **Linux** (ou **WSL 2** no Windows). 

Você precisará das seguintes ferramentas instaladas no seu sistema:
* Compilador **GCC** (`build-essential`).
* **SDL3** (Instalado e compilado a partir do código-fonte, pois as versões de repositórios padrão costumam estar desatualizadas).
* Bibliotecas do sistema para interface gráfica (Wayland/X11) e `libutil`.

### Instalando dependências no Ubuntu/WSL:
```bash
sudo apt update
sudo apt install build-essential git cmake libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxi-dev libxkbcommon-dev libgl1-mesa-dev libwayland-dev libxss-dev libxtst-dev libxfixes-dev
```

*(Consulte a documentação oficial do SDL3 para instruções de compilação da biblioteca na sua máquina).*

---

## 🚀 Como Compilar e Executar

1. Clone este repositório para o sistema de arquivos do Linux (ex: `~/workspace/terminal-and-shell`) para garantir a máxima performance:
   ```bash
   git clone [https://github.com/SEU_USUARIO/terminal-and-shell.git](https://github.com/SEU_USUARIO/terminal-and-shell.git)
   cd terminal-and-shell
   ```

2. Compile o código-fonte linkando as bibliotecas do SDL3 e utilitários POSIX:
   ```bash
   gcc main.c -o main -lSDL3 -lutil
   ```

3. (Opcional) Se o sistema não encontrar a biblioteca dinâmica do SDL3 na hora de rodar, atualize o cache de bibliotecas:
   ```bash
   sudo ldconfig
   ```

4. Execute o emulador:
   ```bash
   ./main
   ```
   
---

## 🛠️ Tecnologias Utilizadas
* **Linguagem:** C
* **Gráficos/Janela:** [SDL3 (Simple DirectMedia Layer)](https://github.com/libsdl-org/SDL)
* **APIs de Sistema:** POSIX (pty, fork, execve, fcntl)
