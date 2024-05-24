# **squares.org solver**
Solver do jogo squares.org usando DFS (Busca em profundidade)

- **solver.c**: Faz a busca e escreve as palavras encontradas e as posições das letras em um arquivo de saída.
- **auto.py**: Lê o arquivo de saída gerado pelo solver e mexe o mouse automaticamente para colocar as palavras.

**Disclaimer: o solver não encontra sempre todas as palavras do jogo: depende do dicionário interno deles**

# **Uso**

## *solver.c*

O solver depende apenas da lib *Hunspell*, que verifica se a palavra encontrada é uma palavra válida. Para instalar no Ubuntu:

```
sudo apt-get install libhunspell-dev
```

Para compilar o programa basta usar o comando ```make``` no diretório do projeto.

Para rodar:
```
./solver <tamanho máximo das palavras> <letras> <caminho do arquivo de saída>
```

Ex: ```./solver 7 ifbzerpiedvheniw saida.txt```

## *auto.py*

auto.py depende das libs *pyautogui* (mover e clicar automaticamente), *keyboard* (cancelar a execução) e *argparse* (receber parâmetros da execução). Para instalar, basta executar ```pip install -r requirements.txt```

Para rodar:
```
py auto.py <caminho do arquivo com as palavras e posições> <delay em segundos até começar a resolver>
```

**Para interromper a execução, basta pressionar a tecla 'q'**