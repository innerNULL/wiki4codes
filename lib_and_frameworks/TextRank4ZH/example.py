# -*- coding: utf-8 -*-


from textrank4zh import TextRank4Keyword, TextRank4Sentence


text = \
"""
个人不赞同你说的这个观点。其一，养狗的都知道的，狗子小便一般都会选择一些较为偏僻的地方，如一些小角落等。而你说的在轮胎拉一大坨那么多，可能性比较小，他们在那些地方小便纯属做标记，可能就一小点，甚至就几滴，都不会弄到轮胎上。这就好比你遇到美人儿，想给他要微信一样，但人和狗子最大的差别就是，他的微信到处贴着，而人的微信还要甄别一下加不加的问题。我家两狗子，有过这方面的经历。做标记不管是在轮胎还是别的地方，量真的很少。其二，狗始终是狗，说难听点是畜牲，就算你训练的再好也拗不过他的天性，更别说我们普普通通的铲屎官，连大家经常呼吁的铲屎，能做到日常铲屎已经非常好了。大家的思想都在改变，呼吁大家铲屎就非常可，解决小便这事还真不可行，毕竟太不人道注意了。我看有些铲屎官也说就公共建设没有涉及宠物这一类的，比如说建立狗子专用的厕所，到对于狗子爱做标记这一点来说，也不是说建立这些就能改变狗子的天性的。其三，希望大家狗子宽容一些，这么苛刻的要求，狗子表示真的做不到(⊙o⊙)哇。相互理解是人类进步的阶梯，理解万岁。
"""


if __name__ == "__main__":
    print(text)

    tr4s = TextRank4Sentence()
    tr4s.analyze(text=text, lower=True, source = 'all_filters') 

    for item in tr4s.get_key_sentences(num=3):
        print(item.index, item.weight, item.sentence)
