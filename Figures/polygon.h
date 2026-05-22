import numpy as np
import time
import pyautogui
import cv2
import mss
from skimage.measure import label, regionprops
from skimage.morphology import remove_small_objects

# =========================
# ЗОНА ЭКРАНА
# =========================
monitor = {'left': 300, 'top': 150, 'width': 800, 'height': 250}

pyautogui.PAUSE = 0.01

last_jump_time = 0
last_duck_time = 0
jump_cooldown = 0.15
duck_cooldown = 0.4
game_started = False

def check_game_over(binary):
    """Проверяет, не закончилась ли игра (ищет GAME OVER)"""
    # GAME OVER - это красные буквы, которые будут видны при инверсии
    mask = binary > 128
    mask = remove_small_objects(mask, min_size=100)
    
    labeled = label(mask)
    props = regionprops(labeled)
    
    # Ищем большие объекты в центре экрана (GAME OVER текст)
    for obj in props:
        y1, x1, y2, x2 = obj.bbox
        h = y2 - y1
        w = x2 - x1
        cy = (y1 + y2) // 2
        cx = (x1 + x2) // 2
        
        # GAME OVER примерно в центре по вертикали и широкий
        if 80 < cy < 180 and w > 200 and h > 30:
            return True
    return False

def restart_game():
    """Перезапускает игру нажатием пробела"""
    print("RESTARTING GAME...")
    pyautogui.press('space')
    time.sleep(0.5)

def detect_obstacles(binary):
    now = time.time()
    
    # Инверсия
    mask = binary > 128
    mask = remove_small_objects(mask, min_size=50)
    
    labeled = label(mask)
    props = regionprops(labeled)
    
    obstacles = []
    for obj in props:
        y1, x1, y2, x2 = obj.bbox
        h = y2 - y1
        w = x2 - x1
        area = obj.area
        cx = (x1 + x2) // 2
        cy = (y1 + y2) // 2
        
        # ФИЛЬТРАЦИЯ
        if area < 50 or area > 2000:
            continue
        if w > 100 and h < 20:  # Текст
            continue
        # Пропускаем GAME OVER (в центре экрана)
        if 80 < cy < 180 and w > 150:
            continue
        # Пропускаем кнопку рестарта (в центре)
        if 100 < cy < 200 and 300 < cx < 500:
            continue
        
        obstacles.append({
            'x1': x1, 'y1': y1, 'x2': x2, 'y2': y2,
            'cx': cx, 'cy': cy, 'w': w, 'h': h, 'area': area
        })
    
    obstacles.sort(key=lambda x: x['cx'])
    return obstacles

def should_jump(obstacle, frame_width):
    global last_jump_time
    
    now = time.time()
    cx = obstacle['cx']
    cy = obstacle['cy']
    h = obstacle['h']
    area = obstacle['area']
    
    # Кактусы внизу (y > 150)
    if cy < 150:
        return False
    
    distance = frame_width - cx
    
    if area < 200 and h < 40:
        jump_distance = 150
    elif area < 500 and h < 60:
        jump_distance = 180
    else:
        jump_distance = 200
    
    if distance < jump_distance and distance > 50:
        if now - last_jump_time > jump_cooldown:
            return True
    
    return False

def should_duck(obstacle, frame_width):
    global last_duck_time
    
    now = time.time()
    cx = obstacle['cx']
    cy = obstacle['cy']
    
    if cy > 150:
        return False
    
    distance = frame_width - cx
    
    if distance < 120 and distance > 40:
        if now - last_duck_time > duck_cooldown:
            return True
    
    return False

# =========================
# СТАРТ
# =========================
print("Starting in 3 seconds...")
print("Нажми Q для выхода")
time.sleep(3)

# Запускаем игру в первый раз
print("Starting game...")
pyautogui.press('space')
time.sleep(1)

with mss.mss() as sct:
    while True:
        screenshot = np.array(sct.grab(monitor))
        gray = cv2.cvtColor(screenshot, cv2.COLOR_BGR2GRAY)
        _, binary = cv2.threshold(gray, 100, 255, cv2.THRESH_BINARY_INV)
        
        # Проверяем GAME OVER
        if check_game_over(binary):
            print("GAME OVER detected!")
            restart_game()
            continue
        
        obstacles = detect_obstacles(binary)
        frame_width = monitor['width']
        
        # Отладочная информация
        if len(obstacles) > 0:
            nearest = obstacles[0]
            distance = frame_width - nearest['cx']
            print(f"Obstacle: area={nearest['area']}, pos=({nearest['cx']}, {nearest['cy']}), dist={distance}")
        
        # Проверяем препятствия
        jumped = False
        for obs in obstacles:
            if should_jump(obs, frame_width):
                print(f"JUMP! Distance: {frame_width - obs['cx']}")
                pyautogui.keyUp('down')
                pyautogui.press('space')
                last_jump_time = time.time()
                jumped = True
                break
            
            elif should_duck(obs, frame_width):
                print(f"DUCK! Bird at y={obs['cy']}")
                pyautogui.keyDown('down')
                last_duck_time = time.time()
                time.sleep(0.4)
                pyautogui.keyUp('down')
                jumped = True
                break
        
        if not jumped and len(obstacles) > 0:
            print(f"No action taken for nearest obstacle")
        
        # =====================
        # DEBUG ОКНО
        # =====================
        debug = cv2.cvtColor(binary, cv2.COLOR_GRAY2BGR)
        
        cv2.line(debug, (frame_width - 200, 0), (frame_width - 200, monitor['height']), (0, 255, 0), 1)
        cv2.line(debug, (frame_width - 150, 0), (frame_width - 150, monitor['height']), (255, 255, 0), 1)
        cv2.line(debug, (frame_width - 100, 0), (frame_width - 100, monitor['height']), (255, 0, 0), 1)
        
        for obs in obstacles:
            color = (0, 255, 255)
            if obs['cy'] < 150:
                color = (0, 0, 255)
            
            cv2.rectangle(debug, (obs['x1'], obs['y1']), (obs['x2'], obs['y2']), color, 2)
            cv2.putText(debug, f"{obs['area']}", (obs['x1'], obs['y1']-5), 
                       cv2.FONT_HERSHEY_SIMPLEX, 0.4, color, 1)
        
        cv2.imshow("debug", debug)
        
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

cv2.destroyAllWindows()
pyautogui.keyUp('down')
pyautogui.keyUp('space')
print("Stopped")