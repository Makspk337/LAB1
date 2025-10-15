package main

type QNode struct {
    data string
    next *QNode
}

type Queue struct {
    name string
    head *QNode
    tail *QNode
    size int
}

func createQueue(name string) *Queue {
    return &Queue{
        name: name,
        head: nil,
        tail: nil,
        size: 0,
    }
}

func (q *Queue) push(data string) {
    node := &QNode{data: data, next: nil}
    if q.head == nil {
        q.head = node
        q.tail = node
    } else {
        q.tail.next = node
        q.tail = node
    }
    q.size++
}

func (q *Queue) pop() string {
    if q.head == nil {
        return ""
    }
    data := q.head.data
    q.head = q.head.next
    if q.head == nil {
        q.tail = nil
    }
    q.size--
    return data
}

func (q *Queue) peek() string {
    if q.head == nil {
        return ""
    }
    return q.head.data
}

func (q *Queue) isEmpty() bool {
    return q.size == 0
}

func (q *Queue) read() string {
    result := ""
    cur := q.head
    for cur != nil {
        result += cur.data
        if cur.next != nil {
            result += " "
        }
        cur = cur.next
    }
    return result
}
