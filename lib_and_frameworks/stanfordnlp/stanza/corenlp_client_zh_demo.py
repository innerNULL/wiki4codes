# -*- coding: utf-8 -*-
# file: corenlp_client_demo.py
# date: 2022-02-23


import os
import sys

CURR_DIR: str = os.path.abspath(
    os.path.dirname(__file__))

import datetime
import stanza
from typing import List
from stanza.server import CoreNLPClient


properties = {
    # segment
    "tokenize.language": "zh",
    "segment.model": "edu/stanford/nlp/models/segmenter/chinese/ctb.gz",
    "segment.sighanCorporaDict": "edu/stanford/nlp/models/segmenter/chinese",
    "segment.serDictionary": "edu/stanford/nlp/models/segmenter/chinese/dict-chris6.ser.gz",
    "segment.sighanPostProcessing": "true",
	# sentence split
    "ssplit.boundaryTokenRegex": "[.。]|[!?！？]+",
    # pos
    "pos.model": "edu/stanford/nlp/models/pos-tagger/chinese-distsim/chinese-distsim.tagger",
    # ner
    "ner.language": "chinese",
    "ner.model": "edu/stanford/nlp/models/ner/chinese.misc.distsim.crf.ser.gz",
    "ner.applyNumericClassifiers": "true",
    "ner.useSUTime": "false",
    # regexner
    "ner.fine.regexner.mapping": "edu/stanford/nlp/models/kbp/chinese/gazetteers/cn_regexner_mapping.tab",
    "ner.fine.regexner.noDefaultOverwriteLabels": "CITY,COUNTRY,STATE_OR_PROVINCE"
}


def register_corenlp_path(corenlp_root: str) -> None:
    corenlp_root = os.path.abspath(corenlp_root)
    os.environ['CORENLP_HOME'] = corenlp_root


def init() -> None:
    corenlp_root: str = os.path.join(CURR_DIR, "_corenlp")
    stanza.install_corenlp(corenlp_root)
    stanza.download_corenlp_models(
        model='chinese', version='4.4.0', dir=corenlp_root, force=False)

    # export CORENLP_HOME=/home/liuyutong/project/personal/wiki4codes/lib_and_frameworks/stanfordnlp/stanza/_corenlp
    # for file in `find $CORENLP_HOME -name "*.jar"`; do export 
    # CLASSPATH="$CLASSPATH:`realpath $file`"; done
    # or
    register_corenlp_path(corenlp_root)


def get_corenlp_client(preload: bool=True) -> CoreNLPClient:
    annotators=['tokenize','ssplit','pos','lemma','ner', 'parse', 'depparse','coref']
    annotators=['tokenize','ssplit']
    #corenlp_client: CoreNLPClient = CoreNLPClient(
    #    annotators=annotators, timeout=30000, memory='6G', properties=properties)
    # or
    corenlp_client: CoreNLPClient = CoreNLPClient(
        annotators=annotators, timeout=30000, memory='6G', properties="zh")

    if preload:
        corenlp_client.annotate("")
    return corenlp_client


if __name__ == "__main__":
    init()
    corenlp_client: CoreNLPClient = get_corenlp_client()

    test: str = """
    接下来，在云计算、数字化转型的时代浪潮里，Workday 开足了马力，抢食着 Oracle 的市场。2019 年《财富》未来 50 强榜单公布，Workday 排名第一。公司上市后市值一度超过 600 亿美元，成为全球 HR SaaS 垂直领域的佼佼者。这是一个足够热血的硅谷创业故事。

Workday 还有一个被人传颂的公司信条，并逐渐演化成为了不少硅谷公司企业理念的一部分——「快乐的员工=好的客户」。

企业努力让雇员工作得开心、实现价值永远是一件性感的事情。中国互联网公司们曾一度效仿 Facebook、谷歌、Netflix 等公司的企业文化来吸引新的人才加入，并引以为荣。

Workday 的热血故事背后，一个容易被人忽略的事实是：它的风靡其实是近些年数字化转型快速发展的缩影。如微软的 CEO Staya Nadella 所说：「每个公司都将成为软件公司。我们必须开始思考如何像数字化公司一样运营，不再是单纯采购解决方案、应用系统软件。我们必须思考如何成为数字化公司。」

这成为了一种共识，「数字化」被当作一剂解药：降本增效，解决企业现有的发展问题，带来明日的增长。而人是世界上最难以看透的东西，数字化领域里最复杂的便是人的数字化。帮助企业解决了人的数字化问题的 Workday
也因此获得了巨大的成功。"""

    for i in range(10):
        print(datetime.datetime.now(), "one time's cumpute")
        ann = corenlp_client.annotate(test)

    doc = corenlp_client.annotate(test)
    for i, sent in enumerate(doc.sentence):
        print("sentence {}: ".format(i))
        splitted_sent: str = ""
        for j, token in enumerate(sent.token):
            splitted_sent = splitted_sent + token.word + " "
        print(splitted_sent)
