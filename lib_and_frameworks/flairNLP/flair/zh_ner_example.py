# -*- coding: utf-8 -*-
# file: example.py
# date: 2022-02-10


import flair.datasets
from flair.data import Sentence, Dictionary
from flair.tokenization import JapaneseTokenizer
from flair.datasets.sequence_labeling import NER_CHINESE_WEIBO
from flair.embeddings import WordEmbeddings, StackedEmbeddings
from flair.models import SequenceTagger
from flair.trainers import ModelTrainer
from typing import List


def get_weibo_ner_dataset() -> NER_CHINESE_WEIBO:
    corpus: NER_CHINESE_WEIBO = flair.datasets.NER_CHINESE_WEIBO()
    return corpus


def get_zh_fasttext_embedding() -> WordEmbeddings:
    return WordEmbeddings('zh')


def train(
        model: SequenceTagger, corpus: NER_CHINESE_WEIBO
) -> None:
    trainer = ModelTrainer(tagger, weibo_ner)
    trainer.train(
        path='resources/taggers/sota-ner-flair',
        learning_rate=0.1,
        mini_batch_size=32,
        max_epochs=150)


if __name__ == "__main__":
    weibo_ner: NER_CHINESE_WEIBO = get_weibo_ner_dataset()
    label_type: str = "ner"
    label_dict: Dictionary = weibo_ner.make_label_dictionary(
        label_type=label_type)

    zh_fasttext_emd: WordEmbeddings = get_zh_fasttext_embedding()
    embedding_types: List[WordEmbeddings] = [
            zh_fasttext_emd
    ]
    embeddings: StackedEmbeddings = StackedEmbeddings(embeddings=embedding_types)

    tagger = SequenceTagger(
        hidden_size=256,
        embeddings=embeddings, tag_dictionary=label_dict,
        tag_type=label_type, use_crf=True)

    #train()
    tagger = SequenceTagger.load("./resources/taggers/sota-ner-flair/best-model.pt")

    test_text: str = """ 
    我 叫 周 杰 伦
    """
    test_sent: Sentence = Sentence(test_text.split(" "))
    tagger.predict(test_sent, all_tag_prob=True)
    print(test_sent)




