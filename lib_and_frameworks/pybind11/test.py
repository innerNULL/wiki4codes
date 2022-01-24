 

import pymod


if __name__ == "__main__":
    pymod.random_log()

    print(pymod.str_split("a,b,c,d,e", ","))

    person = pymod.Person(22)
    person.give_age(23)
    print(person.get_age())
    person.give_age("22")
    print(person.get_age())

