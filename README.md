# Verger

A C++ exercise of a orchard.

There is 3 types of tree in the orchard: Cherry, apple and peer.

| Tree | Nb fruit | Weight | Growth | Harvest | Rotting |
| ---- | -------- | ------ | ------ | ------- | ------- |
| Cherry | 45.000 to 65.000 | 5 | April | May to June | July to december |
| Apple | 600 to 850 | 150 | April to August | September to November | December |
| Peer | 1600 to 2500 | 90 | April to September | October to November | December |

Every tree go by different steps:
- April: 5% chance to loose all the fruits
- At the start of growth month: a random amount of fruits growth instantly
- Between the start of growth and the end of harvest time: lose 3 to 10% of the fruits each months, due to birds and parasites
- At the end of harvest month to december: lose progressively the fruits

The farmer need to choose when he harvest all his tree, he can choose only 1 month in the year and need to have at least 2000 kg of fruits.

# Install

Clone this repo with command `git clone https://github.com/Tryliom/Verger --recursive`
