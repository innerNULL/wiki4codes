# -*- coding: utf-8 -*- 
# file: ner_demo.py
# date: 2021-12-31


import stanza
from typing import List, Dict
from stanza.pipeline.core import Pipeline
from stanza.models.common.doc import Document
from stanza.models.common.doc import Sentence
from stanza.models.common.doc import Token


def extract_entities(
        doc: Document
) -> List[ List[str] ]:
    entities: List[ List[str] ] = []

    sentence_: Sentence = None
    token_: Token = None
    for sentence in doc.sentences:
        sentence_ = sentence
        curr_entities: List[str] = []
        curr_ner_tags: List[str] = []
        curr_ner_texts: List[str] = []

        for token in sentence.tokens:
            token_ = token
            ner_tag: str = token_.ner
            if "-" in ner_tag:
                curr_ner_tags.append(ner_tag)
                curr_ner_texts.append(token_.text)
            elif ner_tag == "O":
                if len(curr_ner_tags) > 0:
                    if curr_ner_tags[-1] != ner_tag:
                        curr_ner_tags.append(ner_tag)
                        curr_ner_texts.append("")
        
        last_ner_tag: str = ""
        last_ner_text: str = ""
        for i in range(len(curr_ner_tags)):
            curr_ner_tag: str = curr_ner_tags[i]
            curr_ner_text: str = curr_ner_texts[i]
            #print(curr_ner_tag, last_ner_tag)
            #print(curr_ner_text, last_ner_text)

            if last_ner_tag == "":
                last_ner_tag = curr_ner_tag 
                last_ner_text = curr_ner_text
            elif curr_ner_tag == "O":
                curr_entities.append(last_ner_text)
                last_ner_tag = curr_ner_tag
                last_ner_text = curr_ner_text
            elif curr_ner_tag != last_ner_tag:
                curr_entities.append(last_ner_text)
                last_ner_tag = curr_ner_tag
                last_ner_text = curr_ner_text 
            elif curr_ner_tag == last_ner_tag:
                last_ner_text += curr_ner_text
        #print(curr_ner_tags)
        #print(curr_ner_texts)
        #print(curr_entities)
        return curr_entities




if __name__ == "__main__":
    nlp: Pipeline = stanza.Pipeline('zh', processors='tokenize,ner')
    #sentence: str = "吴某凡、赵某薇、张某瀚、王某宏等等，这些曾经众星捧月的顶流明星，估计做梦也没想到，自己会落到这般田地"
    sentence: str = "就在同一页面，输入关键词「北京环球影城」，应用“duang”一下即可识别出意图，给出景区门票预订的方法"
    doc: Document = nlp(sentence)
    entities: List[ List[str] ] = extract_entities(doc)
    print("The input sentence is: %s" % sentence)
    print("The extract entities are: {}".format(entities))
