import nltk

pos = []
neg = []

class Analyzer():
    """Implements sentiment analysis."""
    
    def __init__(self, positives="positive-words.txt", negatives="negative-words.txt"):
        """Initialize Analyzer."""

        # TODO
        
        global pos
        global neg
        
        f = open(positives, 'r')
        
        for line in f:
            if line[:1]!=';':
                pos.append(line)
        
        f.close()
        
        f = open(negatives, 'r')
        
        for line in f:
            if line[:1]!=';':
                neg.append(line)
        
        f.close()

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        
        ret=0
        # TODO
        global pos
        global neg
        
        text=text.split(' ')
        for text_n in text:
            for line in pos:
                line=line.strip()
                if text_n==line:
                    ret=ret+1
            
            for line in neg:
                line=line.strip()
                if text_n==line:
                    ret=ret-1
        
        return ret
