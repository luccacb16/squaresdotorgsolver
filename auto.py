from pynput import mouse
import pyautogui
import keyboard
import time
import argparse

click_pos = []

def calc_pos(click_pos):
    x1, y1 = click_pos[0]
    x2, y2 = click_pos[1]
    
    dx = x2 - x1
    dy = y2 - y1
    
    return [[(x1 + dx * y, y1 + dy * x) for y in range(4)] for x in range(4)]  

def on_click(x, y, button, pressed):
    # Verifica se o botão direito foi pressionado
    if button == mouse.Button.left and pressed:
        click_pos.append((x, y))
        print(f"pos: ({x}, {y})")
        
        if len(click_pos) >= 2:
            return False

def parse_validas_file(file_path):
    words_positions = []
    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines:
            parts = line.strip().split('|')
            word = parts[0].strip()
            positions = parts[1].strip().split(' -> ')
            coords = []
            for pos in positions:
                x, y = map(int, pos.strip('()').split(','))
                coords.append((x, y))
            words_positions.append((word, coords))
    return words_positions

def solve(results, letras_pos):
    for word, positions in results:
        if keyboard.is_pressed('q'):
            print('Tecla de escape pressionada, parando...')
            break
        
        print(f'Palavra: {word} | Posições: {positions}')
        start_x, start_y = letras_pos[positions[0][0]][positions[0][1]]
        
        pyautogui.moveTo(start_x, start_y)
        pyautogui.mouseDown()
        
        for pos in positions[1:]:
            next_x, next_y = letras_pos[pos[0]][pos[1]]
            pyautogui.moveTo(next_x, next_y, duration=0.05)
        
        pyautogui.mouseUp()
        time.sleep(0.7)

def main():
    parser = argparse.ArgumentParser(description='squares.org autosolver')
    parser.add_argument('file_path', type=str, help='Caminho para o arquivo de palavras válidas')
    parser.add_argument('sleep_time', type=int, help='Tempo em segundos para o delay inicial')

    args = parser.parse_args()

    words_positions = parse_validas_file(args.file_path)
    
    with mouse.Listener(on_click=on_click) as listener:
        print("Clique com o botão esquerdo para registrar as posições. Ouvindo os dois cliques...")
        listener.join()
    print()
    
    letras_pos = calc_pos(click_pos)
    
    print(f'Iniciando em:')
    for i in range(args.sleep_time, 0, -1):
        print(f'{i}')
        time.sleep(1)
    print('Resolvendo!\n')

    solve(words_positions, letras_pos)

if __name__ == "__main__":
    main()