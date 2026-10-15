x = "global"


def show():
    print(x)


def call():
    x = "local"
    show()


call()
