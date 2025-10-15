package main

type FNode struct {
    value string
    next  *FNode
}

type ForwardList struct {
    name string
    head *FNode
}

func createForwardList(name string) *ForwardList {
    return &ForwardList{
        name: name,
        head: nil,
    }
}

func (list *ForwardList) pushHead(value string) {
    node := &FNode{value: value, next: list.head}
    list.head = node
}

func (list *ForwardList) pushTail(value string) {
    node := &FNode{value: value, next: nil}
    if list.head == nil {
        list.head = node
        return
    }
    cur := list.head
    for cur.next != nil {
        cur = cur.next
    }
    cur.next = node
}

func (list *ForwardList) pushBefore(before, value string) {
    if list.head == nil {
        return
    }
    if list.head.value == before {
        list.pushHead(value)
        return
    }
    cur := list.head
    for cur.next != nil && cur.next.value != before {
        cur = cur.next
    }
    if cur.next != nil {
        node := &FNode{value: value, next: cur.next}
        cur.next = node
    }
}

func (list *ForwardList) pushAfter(after, value string) {
    cur := list.head
    for cur != nil && cur.value != after {
        cur = cur.next
    }
    if cur != nil {
        node := &FNode{value: value, next: cur.next}
        cur.next = node
    }
}

func (list *ForwardList) deleteHead() {
    if list.head == nil {
        return
    }
    list.head = list.head.next
}

func (list *ForwardList) deleteTail() {
    if list.head == nil {
        return
    }
    if list.head.next == nil {
        list.head = nil
        return
    }
    cur := list.head
    for cur.next.next != nil {
        cur = cur.next
    }
    cur.next = nil
}

func (list *ForwardList) deleteBefore(value string) {
    if list.head == nil || list.head.value == value {
        return
    }
    if list.head.next != nil && list.head.next.value == value {
        list.deleteHead()
        return
    }
    prev := list.head
    cur := list.head.next
    for cur.next != nil && cur.next.value != value {
        prev = cur
        cur = cur.next
    }
    if cur.next != nil {
        prev.next = cur.next
    }
}

func (list *ForwardList) deleteAfter(value string) {
    cur := list.head
    for cur != nil && cur.value != value {
        cur = cur.next
    }
    if cur != nil && cur.next != nil {
        cur.next = cur.next.next
    }
}

func (list *ForwardList) deleteValue(value string) {
    if list.head == nil {
        return
    }
    if list.head.value == value {
        list.deleteHead()
        return
    }
    prev := list.head
    cur := list.head.next
    for cur != nil && cur.value != value {
        prev = cur
        cur = cur.next
    }
    if cur != nil {
        prev.next = cur.next
    }
}

func (list *ForwardList) find(value string) bool {
    cur := list.head
    for cur != nil {
        if cur.value == value {
            return true
        }
        cur = cur.next
    }
    return false
}

func (list *ForwardList) read() string {
    result := ""
    cur := list.head
    for cur != nil {
        result += cur.value
        if cur.next != nil {
            result += " "
        }
        cur = cur.next
    }
    return result
}

func (list *ForwardList) readReverse() string {
    if list.head == nil {
        return ""
    }
    
    // Собираем значения в слайс
    var values []string
    cur := list.head
    for cur != nil {
        values = append(values, cur.value)
        cur = cur.next
    }
    
    // Формируем строку в обратном порядке
    result := ""
    for i := len(values) - 1; i >= 0; i-- {
        result += values[i]
        if i > 0 {
            result += " "
        }
    }
    return result
}
