import Practising_submodule_adding.bmi as bmi


def test_bmi_normal_weight():
    height=1.75
    weight=65
    output =bmi.calculate_bmi(height,weight)
    x=bmi.classify_bmi(output)
    assert(x==0)
   
def test_bmi_over_weight():
    height=1.58
    weight=105
    output =bmi.calculate_bmi(height,weight)
    x=bmi.classify_bmi(output)
    assert(x==1)
def test_bmi_under_weight():
    height=1.95
    weight=45
    output =bmi.calculate_bmi(height,weight)
    x=bmi.classify_bmi(output)
    assert(x==-1)