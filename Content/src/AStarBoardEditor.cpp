#include "AStarBoardEditor.h"

void AStarBoardEditor::Start()
{
    SceneObject::Start();
    
    startButton->Start();
    nextButton->Start();
    previousButton->Start();
    restartButton->Start();
    wallButton->Start();
    portalButton->Start();
    checkpointButton->Start();
    startCellButton->Start();
    endCellButton->Start();
    emptyButton->Start();
}

void AStarBoardEditor::Update()
{
    SceneObject::Update();

    startButton->Update();
    nextButton->Update();
    previousButton->Update();
    restartButton->Update();
    wallButton->Update();
    portalButton->Update();
    checkpointButton->Update();
    startCellButton->Update();
    endCellButton->Update();
    emptyButton->Update();
}

void AStarBoardEditor::Draw()
{
    SceneObject::Draw();

    startButton->Draw();
    nextButton->Draw();
    previousButton->Draw();
    restartButton->Draw();
    wallButton->Draw();
    portalButton->Draw();
    checkpointButton->Draw();
    startCellButton->Draw();
    endCellButton->Draw();
    emptyButton->Draw();
}

bool AStarBoardEditor::Contains(sf::Vector2i position)
{
    return false;
}
