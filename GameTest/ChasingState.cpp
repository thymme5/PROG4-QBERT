#include "ChasingState.h"
#include "CoilyComponent.h"
#include "TileComponent.h"
#include "QbertMoveComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"

void ChasingState::Enter(CoilyComponent& coily)
{
    //set snake sprite
    auto* texture = coily.GetOwner()->GetComponent<dae::TextureComponent>();
    if (texture)
        texture->SetTexture("testing/coily_snake_test_character.png");

    std::cout << "Coily entered chasing state.\n";
}

void ChasingState::Update(CoilyComponent& coily)
{
    if (coily.IsJumping()) return;

    auto coilyTile = coily.GetCoilyTile();
    auto qbertTile = coily.GetQbertTile();
    if (!coilyTile || !qbertTile) return;

    auto [cr, cc] = coilyTile->GetGridPosition();
    auto [qr, qc] = qbertTile->GetGridPosition();

    std::cout << "Coily at (" << cr << "," << cc << ") -> Q*bert at (" << qr << "," << qc << ")\n";

    Direction dir;

    if (qr > cr && qc > cc)
        dir = Direction::DownRight;
    else if (qr > cr && qc <= cc)
        dir = Direction::DownLeft;
    else if (qr < cr && qc >= cc)
        dir = Direction::UpRight;
    else if (qr < cr && qc < cc)
        dir = Direction::UpLeft;
    else
        return; // Already on same tile

    coily.TryMove(dir);
}


void ChasingState::Exit(CoilyComponent& coily)
{
    coily;
    std::cout << "Coily exited chasing state.\n";
}
