function Node(data) {
    this.data = data
    this.parent = null
    this.children = []
}

function Tree(data) {
    let node = new Node(data)
    this._root = node
}

var tree = new Tree("Root")

Tree.prototype.forEach = function (callback, node) {
    for (var i = 0, length = node.children.length; i < length; i++) {
        let child = node.children[i]
        this.forEach(callback, child)
    }
    callback(node)
}

Tree.prototype.traverseDF = function (callback) {
    (function recurse(currentNode) {
        for (var i = 0, length = currentNode.children.length; i < length; i++) {
            recurse(currentNode.children[i])
        }
        callback(currentNode)
    })(this._root)
}

Tree.prototype.traverseBF = function (callback) {
    var queue = new Queue()

    queue.enqueue(this._root)

    let currentNode = queue.dequeue()

    while (currentNode) {
        for (var i = 0, length = currentNode.children.length; i < length; i++) {
            queue.enqueue(currentNode.children[i])
        }

        callback(currentNode)
        currentNode = queue.dequeue()
    }
}

Tree.prototype.contains = function (callback, traversal) {
    traversal.call(this, callback)
}

Tree.prototype.add = function (data, toData, traversal) {
    var child = new Node(data), parent = null, callback = function (node) {
        if (node.data === toData) {
            parent = node
        }
    }
    this.contains(callback, traversal)
    if (parent) {
        child.parent = parent
        parent.children.push(child)
    } else {
        throw new Error('Cannot add node to a non-existent parent.')
    }
}

Tree.prototype.remove = function (data, fromData, traversal) {
    var tree = this, parent = null, childToRemove = null, index
    var callback = function (node) {
        if (node.data === fromData) {
            parent = node
        }
    }
    this.contains(callback, traversal)
    if (parent) {
        index = findIndex(parent.children, data)
        if (index === undefined) {
            throw new Error('Node to remove does not exist.')
        } else {
            childToRemove = parent.children.splice(index, 1)
        }
    } else {
        throw new Error('Parent does not exist.')
    }
    return childToRemove
}
function findIndex(arr, data) {
    var index
    for (var i = 0; i < arr.length; i++) {
        if (arr[i].data === data) {
            index = i
        }
    }

    return index
}

function Queue() {
    this._oldestIndex = 1
    this._newestIndex = 1
    this._storage = {}
}

Queue.prototype.size = function () {
    return this._newestIndex - this._oldestIndex
}

Queue.prototype.enqueue = function (data) {
    this._storage[this._newestIndex] = data
    this._newestIndex++
}

Queue.prototype.dequeue = function () {
    var oldestIndex = this._oldestIndex, newestIndex = this._newestIndex, deletedData

    if (oldestIndex !== newestIndex) {
        deletedData = this._storage[oldestIndex]
        delete this._storage[oldestIndex]
        this._oldestIndex++

        return deletedData
    }
}
