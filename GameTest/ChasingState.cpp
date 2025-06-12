#include "ChasingState.h"
#include "CoilyComponent.h"
#include "TileComponent.h"
#include "QbertMoveComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"

void ChasingState::Enter(CoilyComponent& coily)
{
    std::cout << "Coily entered chasing state.\n";
    coily;
}

void ChasingState::Update(CoilyComponent& coily)
{
    if (coily.IsJumping()) return;

    auto coilyTile = coily.GetCoilyTile();
    auto qbertTile = coily.GetQbertTile();
    if (!coilyTile || !qbertTile) return;

    auto [cr, cc] = coilyTile->GetGridPosition(); //coily row, coily col
    auto [qr, qc] = qbertTile->GetGridPosition(); // qbert row, qbert col

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
        return; 

    coily.TryMove(dir);
}


void ChasingState::Exit(CoilyComponent& coily)
{
    coily;
    std::cout << "Coily exited chasing state.\n";
}
