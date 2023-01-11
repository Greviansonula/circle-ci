from main import Add

def TestAdd():
    assert Add(2,3) == 5
    assert Add(5, 60) == 65
    print("Add Function works orrectly")


if __name__ == "__main__":
    TestAdd()