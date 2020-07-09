from jq6500 import Player
import time

player = Player(port=1, volume=30)

ho = "1026591258"
player.set_volume(30)
time.sleep(2)
for i in range(len(ho)):
    player.play_by_index(10-int(ho[i]))
    time.sleep(0.9)
