#include "joy.h"
#include "engine.h"

Shit::Shit(Suit suit, int number):BasicCard(suit, number){
    setObjectName("shit");
    will_throw = false;
    target_fixed = true;
}

QString Shit::getSubtype() const{
    return "disgusting_card";
}

void Shit::eatShit(Room *room, PlayerStar source) const{
    if(!source->isAlive())
        return;
    LogMessage log;
    log.card_str = getEffectIdString();
    log.from = source;

    if(getSuit() == Spade){
        log.type = "$ShitLostHp";
        room->sendLog(log);
        room->loseHp(source);
        return;
    }

    DamageStruct damage;
    damage.from = damage.to = source;
    damage.card = this;

    switch(getSuit()){
    case Club: damage.nature = DamageStruct::Thunder; break;
    case Heart: damage.nature = DamageStruct::Fire; break;
    default:
        damage.nature = DamageStruct::Normal;
    }

    log.type = "$ShitDamage";
    room->sendLog(log);
    room->damage(damage);
}

void Shit::onMove(const CardMoveStruct &move) const{
    if(move.from && move.from_place == Player::Hand &&
       move.from->getRoom()->getCurrent() == move.from
       && (move.to_place == Player::DiscardedPile || move.to_place == Player::Special)
       && move.to == NULL){
        eatShit(move.from->getRoom(), move.from);
    }
}

void Shit::onUse(Room *room, const CardUseStruct &) const{
    room->moveCardTo(this, NULL, Player::DiscardedPile);
}

bool Shit::HasShit(const Card *card){
    if(card->isVirtualCard()){
        QList<int> card_ids = card->getSubcards();
        foreach(int card_id, card_ids){
            const Card *c = Sanguosha->getCard(card_id);
            if(c->objectName() == "shit")
                return true;
        }

        return false;
    }else
        return card->objectName() == "shit";
}

// -----------  Deluge -----------------

Deluge::Deluge(Card::Suit suit, int number)
    :Disaster(suit, number)
{
    setObjectName("deluge");

    judge.pattern = QRegExp("(.*):(.*):([AK])");
    judge.good = false;
    judge.reason = objectName();
}

void Deluge::takeEffect(ServerPlayer *target) const{
    QList<const Card *> cards = target->getCards("he");

    Room *room = target->getRoom();
    int n = qMin(cards.length(), target->aliveCount());
    if(n == 0)
        return;

    qShuffle(cards);
    cards = cards.mid(0, n);

    QList<int> card_ids;
    foreach(const Card *card, cards){
        card_ids << card->getEffectiveId();
        room->throwCard(card);
    }

    room->fillAG(card_ids);

    QList<ServerPlayer *> players = room->getOtherPlayers(target);
    players << target;
    players = players.mid(0, n);
    foreach(ServerPlayer *player, players){
        if(player->isAlive()){
            int card_id = room->askForAG(player, card_ids, false, "deluge");
            card_ids.removeOne(card_id);

            room->takeAG(player, card_id);
        }
    }

    foreach(int card_id, card_ids)
        room->takeAG(NULL, card_id);

    room->broadcastInvoke("clearAG");
}

// -----------  Typhoon -----------------

Typhoon::Typhoon(Card::Suit suit, int number)
    :Disaster(suit, number)
{
    setObjectName("typhoon");

    judge.pattern = QRegExp("(.*):(diamond):([2-9])");
    judge.good = false;
    judge.reason = objectName();
}

void Typhoon::takeEffect(ServerPlayer *target) const{
    Room *room = target->getRoom();

    QList<ServerPlayer *> players = room->getOtherPlayers(target);
    foreach(ServerPlayer *player, players){
        if(target->distanceTo(player) == 1){
            int discard_num = qMin(6, player->getHandcardNum());
            if(discard_num == 0)
                room->setEmotion(player, "good");
            else{
                room->setEmotion(player, "bad");
                room->broadcastInvoke("animate", "typhoon:" + player->objectName());
                room->broadcastInvoke("playAudio", "typhoon");

                room->askForDiscard(player, objectName(), discard_num);
            }

            room->getThread()->delay();
        }
    }
}

// -----------  Earthquake -----------------

Earthquake::Earthquake(Card::Suit suit, int number)
    :Disaster(suit, number)
{
    setObjectName("earthquake");

    judge.pattern = QRegExp("(.*):(club):([2-9])");
    judge.good = false;
    judge.reason = objectName();
}

void Earthquake::takeEffect(ServerPlayer *target) const{
    Room *room = target->getRoom();
    QList<ServerPlayer *> players = room->getAllPlayers();
    foreach(ServerPlayer *player, players){
        if(target->distanceTo(player) <= 1 ||
           (player->getDefensiveHorse() && target->distanceTo(player) <= 2)){
            if(player->getEquips().isEmpty()){
                room->setEmotion(player, "good");
            }else{
                room->setEmotion(player, "bad");
                room->broadcastInvoke("playAudio", "earthquake");
                player->throwAllEquips();
            }

            room->getThread()->delay();
        }
    }
}

// -----------  Volcano -----------------

Volcano::Volcano(Card::Suit suit, int number)
    :Disaster(suit, number)
{
    setObjectName("volcano");

    judge.pattern = QRegExp("(.*):(heart):([2-9])");
    judge.good = false;
    judge.reason = objectName();
}

void Volcano::takeEffect(ServerPlayer *target) const{
    Room *room = target->getRoom();

    QList<ServerPlayer *> players = room->getAllPlayers();

    foreach(ServerPlayer *player, players){
        int point = player->getDefensiveHorse() && target != player ?
                    3 - target->distanceTo(player) :
                    2 - target->distanceTo(player);
        if(point >= 1){
            DamageStruct damage;
            damage.card = this;
            damage.damage = point;
            damage.to = player;
            damage.nature = DamageStruct::Fire;

            room->broadcastInvoke("playAudio", "volcano");
            room->damage(damage);
        }
    }
}

// -----------  MudSlide -----------------
MudSlide::MudSlide(Card::Suit suit, int number)
    :Disaster(suit, number)
{
    setObjectName("mudslide");

    judge.pattern = QRegExp("(.*):(spade|club):([AK47])");
    judge.good = false;
    judge.reason = objectName();
}

void MudSlide::takeEffect(ServerPlayer *target) const{
    Room *room = target->getRoom();
    QList<ServerPlayer *> players = room->getAllPlayers();
    int to_destroy = 4;
    foreach(ServerPlayer *player, players){
        room->broadcastInvoke("playAudio", "mudslide");

        QList<const Card *> equips = player->getEquips();
        if(equips.isEmpty()){
            DamageStruct damage;
            damage.card = this;
            damage.to = player;
            room->damage(damage);
        }else{
            int i, n = qMin(equips.length(), to_destroy);
            for(i=0; i<n; i++){
                room->throwCard(equips.at(i));
            }

            to_destroy -= n;
            if(to_destroy == 0)
                break;
        }
    }
}

class GrabPeach: public TriggerSkill{
public:
    GrabPeach():TriggerSkill("grab_peach"){
        events << CardUsed;
    }

    virtual bool triggerable(const ServerPlayer *) const{
        return true;
    }

    virtual bool trigger(TriggerEvent, Room* room, ServerPlayer *player, QVariant &data) const{
        CardUseStruct use = data.value<CardUseStruct>();
        if(use.card->inherits("Peach")){
            QList<ServerPlayer *> players = room->getOtherPlayers(player);

            foreach(ServerPlayer *p, players){
                if(p->getOffensiveHorse() == parent() &&
                   p->askForSkillInvoke(objectName(), data))
                {
                    room->throwCard(p->getOffensiveHorse());
                    p->playCardEffect("grab_peach");
                    p->obtainCard(use.card);

                    return true;
                }
            }
        }

        return false;
    }
};

Monkey::Monkey(Card::Suit suit, int number)
    :OffensiveHorse(suit, number)
{
    setObjectName("monkey");

    grab_peach = new GrabPeach;
    grab_peach->setParent(this);
}

void Monkey::onInstall(ServerPlayer *player) const{
    player->getRoom()->getThread()->addTriggerSkill(grab_peach);
}

void Monkey::onUninstall(ServerPlayer *player) const{

}

QString Monkey::getEffectPath(bool ) const{
    return "audio/card/common/monkey.ogg";
}

class GaleShellSkill: public ArmorSkill{
public:
    GaleShellSkill():ArmorSkill("gale-shell"){
        events << Predamaged;
    }

    virtual bool trigger(TriggerEvent, Room* room, ServerPlayer *player, QVariant &data) const{
        DamageStruct damage = data.value<DamageStruct>();
        if(damage.nature == DamageStruct::Fire){
            LogMessage log;
            log.type = "#GaleShellDamage";
            log.from = player;
            log.arg = QString::number(damage.damage);
            log.arg2 = QString::number(damage.damage + 1);
            room->sendLog(log);

            damage.damage ++;
            data = QVariant::fromValue(damage);
        }
        return false;
    }
};

GaleShell::GaleShell(Suit suit, int number)
    :Armor(suit, number){
    setObjectName("gale-shell");
    skill = new GaleShellSkill;

    target_fixed = false;
}

bool GaleShell::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    return targets.isEmpty() && Self->distanceTo(to_select) <= 1;
}

void GaleShell::onUse(Room *room, const CardUseStruct &card_use) const{
    Card::onUse(room, card_use);
}

DisasterPackage::DisasterPackage()
    :Package("disaster")
{
    QList<Card *> cards;

    cards << new Deluge(Card::Spade, 1)
            << new Typhoon(Card::Spade, 4)
            << new Earthquake(Card::Club, 10)
            << new Volcano(Card::Heart, 13)
            << new MudSlide(Card::Heart, 7);

    foreach(Card *card, cards)
        card->setParent(this);

    type = CardPack;
}

JoyPackage::JoyPackage()
    :Package("joy")
{
    QList<Card *> cards;

    cards << new Shit(Card::Club, 1)
            << new Shit(Card::Heart, 8)
            << new Shit(Card::Diamond, 13)
            << new Shit(Card::Spade, 10);

    foreach(Card *card, cards)
        card->setParent(this);

    type = CardPack;
}

class YxSwordSkill: public WeaponSkill{
public:
    YxSwordSkill():WeaponSkill("yx_sword"){
        events << Predamage;
    }

    virtual bool trigger(TriggerEvent, Room* room, ServerPlayer *player, QVariant &data) const{
        DamageStruct damage = data.value<DamageStruct>();
        if(damage.card && damage.card->inherits("Slash") && room->askForSkillInvoke(player, objectName(), data)){
            QList<ServerPlayer *> players = room->getOtherPlayers(player);
            QMutableListIterator<ServerPlayer *> itor(players);

            while(itor.hasNext()){
                itor.next();
                if(!player->inMyAttackRange(itor.value()))
                    itor.remove();
            }

            if(players.isEmpty())
                return false;

            QVariant victim = QVariant::fromValue(damage.to);
            room->setTag("YxSwordVictim", victim);
            ServerPlayer *target = room->askForPlayerChosen(player, players, objectName());
            room->removeTag("YxSwordVictim");
            damage.from = target;
            data = QVariant::fromValue(damage);
            room->moveCardTo(player->getWeapon(), damage.from, Player::Hand);
        }
        return damage.to->isDead();
    }
};

YxSword::YxSword(Suit suit, int number)
    :Weapon(suit, number, 3)
{
    setObjectName("yx_sword");
    skill = new YxSwordSkill;
}

#include "client.h"
#include "standard-skillcards.h"
#include "carditem.h"
class FivelineViewAsSkill: public ViewAsSkill{
public:
    FivelineViewAsSkill():ViewAsSkill("fiveline"){
    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        switch(player->getHp()){
        case 1:
        case 3:
        case 4:
        case 5: return true; break;
        default:
            return false;
        }
    }

    virtual bool viewFilter(const QList<CardItem *> &selected, const CardItem *to_select) const{
        switch(Self->getHp()){
        case 1: return true; break;
        case 3: return selected.length() < 2 && !to_select->isEquipped(); break;
        case 4: return to_select->getCard()->getSuit() == Card::Diamond; break;
        default:
            return false;
        }
    }

    virtual const Card *viewAs(const QList<CardItem *> &cards) const{
        switch(Self->getHp()){
        case 1: {
                if(!cards.isEmpty()){
                    RendeCard *rende_card = new RendeCard;
                    rende_card->addSubcards(cards);
                    return rende_card;
                }
                break;
            }
        case 3: {
                if(cards.length() == 2){
                    JieyinCard *jieyin_card = new JieyinCard();
                    jieyin_card->addSubcards(cards);
                    return jieyin_card;
                }
                break;
            }
        case 4: {
                if(cards.length() == 1){
                    const Card *first = cards.first()->getFilteredCard();
                    Indulgence *indulgence = new Indulgence(first->getSuit(), first->getNumber());
                    indulgence->addSubcard(first);
                    indulgence->setSkillName("guose");
                    return indulgence;
                }
                break;
            }
        case 5 : return new KurouCard; break;
        default:
            break;
        }
        return NULL;
    }
};
/*
class FivelineSkill: public TriggerSkill{
public:
    FivelineSkill():TriggerSkill("fiveline"){
        frequency = Frequent;
        events << CardUsed;
        view_as_skill = new FivelineViewAsSkill;
    }

    virtual int getPriority() const{
        return 2;
    }

    virtual bool trigger(TriggerEvent, Room* room, ServerPlayer *yueying, QVariant &data) const{
        if(yueying->getHp() != 2)
            return false;
        CardUseStruct use = data.value<CardUseStruct>();
        CardStar card = use.card;
        if(card->isNDTrick()){
            if(room->askForSkillInvoke(yueying, "jizhi")){
                room->playSkillEffect("jizhi");
                yueying->drawCards(1);
            }
        }
        return false;
    }
};
*/
Fiveline::Fiveline(Suit suit, int number)
    :Armor(suit, number)
{
    setObjectName("fiveline");
}

void Fiveline::onInstall(ServerPlayer *player) const{
    Room *room = player->getRoom();
    room->attachSkillToPlayer(player, "fiveline");
}

void Fiveline::onUninstall(ServerPlayer *player) const{
    player->getRoom()->detachSkillFromPlayer(player, "fiveline", false);
}

JoyEquipPackage::JoyEquipPackage()
    :Package("joy_equip")
{
    (new Monkey(Card::Diamond, 5))->setParent(this);
    (new GaleShell(Card::Heart, 1))->setParent(this);
    (new YxSword(Card::Club, 9))->setParent(this);
#ifndef USE_RCC
    (new Fiveline(Card::Heart, 5))->setParent(this);
#endif
    skills << new FivelineViewAsSkill;

    type = CardPack;
}

ADD_PACKAGE(Joy)
ADD_PACKAGE(Disaster)
ADD_PACKAGE(JoyEquip)
