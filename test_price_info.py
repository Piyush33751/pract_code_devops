import excersie4 as th_h
price_list={'apple' : 1.20, 'orange':1.40, 'watermelon': 6.50, 'pineapple': 2.70, 'pear' : 0.90, 'papaya': 2.95, 'pomegranate': 4.95 }

quantity_list= {'apple': 5, 'orange':5, 'watermelon': 1, 'pineapple': 2, 'pear' : 10, 'papaya': 1, 'pomegranate': 2 }

def test_total_cost_shopping():
    x=(1.20*5)+(1.40*5)+(6.50*1)+(2.70*2)+(0.90*10)+(2.95*1)+(4.95*2)
    y=th_h.total_cost_shopping()
    assert(x==y)
def test_cost_of_fruit():
    x=1.20 * 10
    y=th_h.cost_of_fruits('apple', 10)
    assert(x==y)