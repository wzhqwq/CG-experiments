//
//  history.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/4/2.
//

#include "history.hpp"

stack<Operation *> opStack;

void Operation::undo() {};

void CreationOp::undo() {
    mainScene->shapes.pop_back();
}

void DeletionOp::undo() {
    mainScene->shapes.insert(mainScene->shapes.begin() + index, geometry);
}

void TranslationOp::undo() {
    geometry->translate(-translation.x, -translation.y);
    if (mainScene->selectedItem)
        mainScene->selectionRect->updateBox(mainScene->selectedItem->getBottomLeft(), mainScene->selectedItem->getTopRight());
}

void ScalingOp::undo() {
    geometry->scale(1 / scaling.x, 1 / scaling.y, center.x, center.y);
    if (mainScene->selectedItem)
        mainScene->selectionRect->updateBox(mainScene->selectedItem->getBottomLeft(), mainScene->selectedItem->getTopRight());
}

void ColoringOp::undo() {
    geometry->currentColor = lastColor;
}

void pushOp(Operation *op) {
    opStack.push(op);
}
void popOp() {
    if (opStack.empty()) return;
    opStack.top()->undo();
    delete opStack.top();
    opStack.pop();
}
