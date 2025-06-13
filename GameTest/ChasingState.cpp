#include "ChasingState.h"
#include "CoilyComponent.h"
#include "TileComponent.h"
#include "QbertMoveComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Observer.h"

void ChasingState::Enter(CoilyComponent&)
{
}

void ChasingState::Update(CoilyComponent& coily)
{
    auto* coilyTexture = coily.GetOwner()->GetComponent<dae::TextureComponent>();
    auto* qbertTexture = coily.GetQbert()->GetOwner()->GetComponent<dae::TextureComponent>();

    if (!coilyTexture || !qbertTexture)
        return;

    const auto coilyPos = coily.GetOwner()->GetTransform().GetPosition();
    const auto qbertPos = coily.GetQbert()->GetOwner()->GetTransform().GetPosition();

    const auto coilySize = coilyTexture->GetTexture()->GetSize();   // returns {width, height}
    const auto qbertSize = qbertTexture->GetTexture()->GetSize();   // returns {width, height}

    // coily bounds
    float coilyLeft = coilyPos.x;
    float coilyRight = coilyPos.x + coilySize.x;
    float coilyTop = coilyPos.y;
    float coilyBottom = coilyPos.y + coilySize.y;

    // qbert bounds
    float qbertLeft = qbertPos.x;
    float qbertRight = qbertPos.x + qbertSize.x;
    float qbertTop = qbertPos.y;
    float qbertBottom = qbertPos.y + qbertSize.y;

    // collision check
    bool isOverlapping = !(coilyRight < qbertLeft ||
        coilyLeft > qbertRight ||
        coilyBottom < qbertTop ||
        coilyTop > qbertBottom);

    if (isOverlapping)
    {
        coily.GetOwner()->NotifyObservers(dae::Event::CoilyHitPlayer);

    }

    if (coily.IsJumping()) return;

    auto coilyTile = coily.GetCoilyTile();
    auto qbertTile = coily.GetQbertTile();

    if (!coilyTile || !qbertTile) return;

    auto [cr, cc] = coilyTile->GetGridPosition(); //coily row, coily col
    auto [qr, qc] = qbertTile->GetGridPosition(); // qbert row, qbert col

    // already on the same tile
    if (qr == cr && qc == cc)
    {
        return; 
    }

    std::cout << "Coily at (" << cr << "," << cc << ") -> Q*bert at (" << qr << "," << qc << ")\n";

    int rowDiff = qr - cr;
    int colDiff = qc - cc;

    Direction dir;

    if (rowDiff > 0 && colDiff > 0)
        dir = Direction::DownRight;
    else if (rowDiff > 0 && colDiff <= 0)
        dir = Direction::DownLeft;
    else if (rowDiff <= 0 && colDiff > 0)
        dir = Direction::UpRight;
    else // rowDiff <= 0 && colDiff <= 0
        dir = Direction::UpLeft;

    coily.TryMove(dir);
}

void ChasingState::Exit(CoilyComponent&)
{
}
