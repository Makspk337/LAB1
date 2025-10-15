package main

type DNode struct {
    value string
    next  *DNode
    prev  *DNode
}

type DoublyList struct {
    name string
    head *DNode
    tail *DNode
}

func createDoublyList(name string) *DoublyList {
    return &DoublyList{
        name: name,
        head: nil,
        tail: nil,
    }
}

func (list *DoublyList) pushHead(value string) {
    node := &DNode{value: value, prev: nil, next: list.head}
    if list.head != nil {
        list.head.prev = node
    }
    list.head = node
    if list.tail == nil {
        list.tail = node
    }
}

func (list *DoublyList) pushTail(value string) {
    node := &DNode{value: value, next: nil, prev: list.tail}
    if list.tail != nil {
        list.tail.next = node
    }
    list.tail = node
    if list.head == nil {
        list.head = node
    }
}

func (list *DoublyList) pushBefore(before, value string) {
    cur := list.head
    for cur != nil && cur.value != before {
        cur = cur.next
    }
    if cur != nil {
        node := &DNode{value: value, next: cur, prev: cur.prev}
        if cur.prev != nil {
            cur.prev.next = node
        } else {
            list.head = node
        }
        cur.prev = node
    }
}

func (list *DoublyList) pushAfter(after, value string) {
    cur := list.head
    for cur != nil && cur.value != after {
        cur = cur.next
    }
    if cur != nil {
        node := &DNode{value: value, prev: cur, next: cur.next}
        if cur.next != nil {
            cur.next.prev = node
        } else {
            list.tail = node
        }
        cur.next = node
    }
}

func (list *DoublyList) deleteHead() {
    if list.head == nil {
        return
    }
    if list.head == list.tail {
        list.head = nil
        list.tail = nil
        return
    }
    list.head = list.head.next
    list.head.prev = nil
}

func (list *DoublyList) deleteTail() {
    if list.tail == nil {
        return
    }
    if list.head == list.tail {
        list.head = nil
        list.tail = nil
        return
    }
    list.tail = list.tail.prev
    list.tail.next = nil
}

func (list *DoublyList) deleteBefore(value string) {
    cur := list.head
    for cur != nil && cur.value != value {
        cur = cur.next
    }
    if cur != nil && cur.prev != nil {
        tmp := cur.prev
        if tmp.prev != nil {
            tmp.prev.next = cur
        } else {
            list.head = cur
        }
        cur.prev = tmp.prev
    }
}

func (list *DoublyList) deleteAfter(value string) {
    cur := list.head
    for cur != nil && cur.value != value {
        cur = cur.next
    }
    if cur != nil && cur.next != nil {
        tmp := cur.next
        cur.next = tmp.next
        if tmp.next != nil {
            tmp.next.prev = cur
        } else {
            list.tail = cur
        }
    }
}

func (list *DoublyList) deleteValue(value string) {
    cur := list.head
    for cur != nil && cur.value != value {
        cur = cur.next
    }
    if cur != nil {
        if cur.prev != nil {
            cur.prev.next = cur.next
        } else {
            list.head = cur.next
        }
        if cur.next != nil {
            cur.next.prev = cur.prev
        } else {
            list.tail = cur.prev
        }
    }
}

func (list *DoublyList) find(value string) bool {
    cur := list.head
    for cur != nil {
        if cur.value == value {
            return true
        }
        cur = cur.next
    }
    return false
}

func (list *DoublyList) read() string {
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

func (list *DoublyList) readReverse() string {
    result := ""
    cur := list.tail
    for cur != nil {
        result += cur.value
        if cur.prev != nil {
            result += " "
        }
        cur = cur.prev
    }
    return result
}
