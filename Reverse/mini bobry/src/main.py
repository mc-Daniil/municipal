def mother_bobr(crown):
    return crown == "NMARK"

def older_mini_bobrik(trunk):
    if len(trunk) != 20:
        return False
    constnant = b'\x14\x00G\x009\x00\x1dvsV\x164\x01\x19sgR\x1d^\x1c'
    res = bytes(a ^ b for a, b in zip(constnant, trunk.encode())).decode("utf-8")
    return res == "C001M1n1B0br1k1W0oow"

def younger_mini_bobrik(root):
    if len(root) != 24:
        return False
    
    parts = [root[i:i+4] for i in range(0, 24, 4)]
    indexes = [2, 4, 3, 5, 0, 1]
    res = ""
    for i in indexes:
        res += parts[i]
        
    return res == "uuur1B0b1M1nrrssD0N0tHuu"


def get_crown(tree):
    return tree[:tree.find("{")]

def get_trunk(tree):
    return tree[tree.find("{") + 1:tree.find("_")]

def get_root(tree):
    return tree[tree.find("_") + 1:tree.find("}")]

def main_bobr():
    try:
        with open("tree.txt", "r") as f:
            tree = f.readline()
            
        if len(tree) != 52:
            print("Your tree is not long enough for mini-bobrs. You've upset the main mini-bobr.")
            return
        
        print("Main mini-bobr likes the tree.")
        print("Let's see if the mother mini-bobr likes your gift.")
        if not mother_bobr(get_crown(tree)):
            print("Mother mini-bobr doesn't like the crown. You've upset the mother mini-bobr.")
            return 
        
        print("Mother mini-bobr likes the crown.")
        print("Let's see if the older mini-bobrik likes your gift.")
        if not older_mini_bobrik(get_trunk(tree)):
            print("Older mini-bobrik doesn't like the trunk. You've upset the older mini-bobr.")
            return
        
        print("Older mini-bobr likes the trunk.")
        print("Let's see if the younger mini-bobrik likes your gift.")
        if not younger_mini_bobrik(get_root(tree)):
            print("Younger mini-bobrik doesn't like the root. You've upset the younger mini-bobr.")
            return
        
        print("Mini-bobrs like your gift. You can go through.")
        
    except FileNotFoundError:
        print("You've come without a tree for us. You've upset the main mini-bobr.")
    except Exception as e:
        print(e)

if __name__ == "__main__":
    main_bobr()