from jq6500 import Player
import time

player = Player(port=1, volume=30)

time.sleep(2)
for i in range(20):
    player.play_by_index(i)
    time.sleep(3)
