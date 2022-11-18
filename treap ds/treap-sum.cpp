int joinValues(int leftValue, int rightValue) {
    return (leftValue + rightValue);
}

int joinDeltas(int oldDelta, int newDelta) {
    return oldDelta + newDelta;
}

int joinValueWithDelta(int value, int delta, int length) {
    return value + delta*length;
}
