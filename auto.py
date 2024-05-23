import pyautogui  # type: ignore
import keyboard  # type: ignore
import time

# Definindo o positionsMap (extraído do notebook)
letras_pos = [
    [(567 + 126 * y, 431 + 126 * x) for y in range(4)] for x in range(4)
]

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
            print('Tecla de escape pressionada, saindo...')
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
    file_path = 'validas.txt'
    words_positions = parse_validas_file(file_path)
    
    time.sleep(3)  # Tempo para o usuário se preparar
    solve(words_positions, letras_pos)

if __name__ == "__main__":
    main()
