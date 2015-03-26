#include <QDebug>
#include "lexer.h"

lexer::lexer()
{
    keywords.insert(QString("add"), itemAdd);
    keywords.insert(QString("all"), itemAll);
    keywords.insert(QString("alter"), itemAlter);
    keywords.insert(QString("and"), itemAnd);
    keywords.insert(QString("any"), itemAny);
    keywords.insert(QString("as"), itemAs);
    keywords.insert(QString("asc"), itemAsc);
    keywords.insert(QString("authorization"), itemAuthorization);
    keywords.insert(QString("backup"), itemBackup);
    keywords.insert(QString("begin"), itemBegin);
    keywords.insert(QString("between"), itemBetween);
    keywords.insert(QString("break"), itemBreak);
    keywords.insert(QString("browse"), itemBrowse);
    keywords.insert(QString("bulk"), itemBulk);
    keywords.insert(QString("by"), itemBy);
    keywords.insert(QString("cascade"), itemCascade);
    keywords.insert(QString("case"), itemCase);
    keywords.insert(QString("check"), itemCheck);
    keywords.insert(QString("checkpoint"), itemCheckpoint);
    keywords.insert(QString("close"), itemClose);
    keywords.insert(QString("clustered"), itemClustered);
    keywords.insert(QString("coalesce"), itemCoalesce);
    keywords.insert(QString("collate"), itemCollate);
    keywords.insert(QString("column"), itemColumn);
    keywords.insert(QString("commit"), itemCommit);
    keywords.insert(QString("compute"), itemCompute);
    keywords.insert(QString("constraint"), itemConstraint);
    keywords.insert(QString("contains"), itemContains);
    keywords.insert(QString("containsTable"), itemContainsTable);
    keywords.insert(QString("continue"), itemContinue);
    keywords.insert(QString("convert"), itemConvert);
    keywords.insert(QString("create"), itemCreate);
    keywords.insert(QString("cross"), itemCross);
    keywords.insert(QString("current"), itemCurrent);
    keywords.insert(QString("current_date"), itemCurrent_Date);
    keywords.insert(QString("current_time"), itemCurrent_Time);
    keywords.insert(QString("current_timestamp"), itemCurrent_Timestamp);
    keywords.insert(QString("current_yser"), itemCurrent_User);
    keywords.insert(QString("cursor"), itemCursor);
    keywords.insert(QString("database"), itemDatabase);
    keywords.insert(QString("dbcc"), itemDbcc);
    keywords.insert(QString("deallocate"), itemDeallocate);
    keywords.insert(QString("declare"), itemDeclare);
    keywords.insert(QString("default"), itemDefault);
    keywords.insert(QString("delete"), itemDelete);
    keywords.insert(QString("deny"), itemDeny);
    keywords.insert(QString("desc"), itemDesc);
    keywords.insert(QString("disk"), itemDisk);
    keywords.insert(QString("distinct"), itemDistinct);
    keywords.insert(QString("distributed"), itemDistributed);
    keywords.insert(QString("double"), itemDouble);
    keywords.insert(QString("drop"), itemDrop);
    keywords.insert(QString("dump"), itemDump);
    keywords.insert(QString("else"), itemElse);
    keywords.insert(QString("end"), itemEnd);
    keywords.insert(QString("errlvl"), itemErrlvl);
    keywords.insert(QString("escape"), itemEscape);
    keywords.insert(QString("except"), itemExcept);
    keywords.insert(QString("exec"), itemExec);
    keywords.insert(QString("execute"), itemExecute);
    keywords.insert(QString("exists"), itemExists);
    keywords.insert(QString("exit"), itemExit);
    keywords.insert(QString("external"), itemExternal);
    keywords.insert(QString("fetch"), itemFetch);
    keywords.insert(QString("file"), itemFile);
    keywords.insert(QString("fillfactor"), itemFillFactor);
    keywords.insert(QString("for"), itemFor);
    keywords.insert(QString("foreign"), itemForeign);
    keywords.insert(QString("freetext"), itemFreeText);
    keywords.insert(QString("freetexttable"), itemFreeTextTable);
    keywords.insert(QString("from"), itemFrom);
    keywords.insert(QString("full"), itemFull);
    keywords.insert(QString("function"), itemFunction);
    keywords.insert(QString("goto"), itemGoto);
    keywords.insert(QString("grant"), itemGrant);
    keywords.insert(QString("group"), itemGroup);
    keywords.insert(QString("having"), itemHaving);
    keywords.insert(QString("holdlock"), itemHoldlock);
    keywords.insert(QString("identity"), itemIdentity);
    keywords.insert(QString("identitycol"), itemIdentityCol);
    keywords.insert(QString("identity_insert"), itemIdentity_Insert);
    keywords.insert(QString("if"), itemIf);
    keywords.insert(QString("in"), itemIn);
    keywords.insert(QString("index"), itemIndex);
    keywords.insert(QString("inner"), itemInner);
    keywords.insert(QString("insert"), itemInsert);
    keywords.insert(QString("intersect"), itemIntersect);
    keywords.insert(QString("into"), itemInto);
    keywords.insert(QString("is"), itemIs);
    keywords.insert(QString("join"), itemJoin);
    keywords.insert(QString("key"), itemKey);
    keywords.insert(QString("kill"), itemKill);
    keywords.insert(QString("left"), itemLeft);
    keywords.insert(QString("like"), itemLike);
    keywords.insert(QString("lineno"), itemLineno);
    keywords.insert(QString("load"), itemLoad);
    keywords.insert(QString("merge"), itemMerge);
    keywords.insert(QString("national"), itemNational);
    keywords.insert(QString("nocheck"), itemNoCheck);
    keywords.insert(QString("nonclustered"), itemNonClustered);
    keywords.insert(QString("not"), itemNot);
    keywords.insert(QString("null"), itemNull);
    keywords.insert(QString("nullif"), itemNullIf);
    keywords.insert(QString("of"), itemOf);
    keywords.insert(QString("off"), itemOff);
    keywords.insert(QString("offsets"), itemOffsets);
    keywords.insert(QString("on"), itemOn);
    keywords.insert(QString("open"), itemOpen);
    keywords.insert(QString("opendatasource"), itemOpenDataSource);
    keywords.insert(QString("openquery"), itemOpenQuery);
    keywords.insert(QString("openrowset"), itemOpenRowset);
    keywords.insert(QString("openxml"), itemOpenXml);
    keywords.insert(QString("option"), itemOption);
    keywords.insert(QString("or"), itemOr);
    keywords.insert(QString("order"), itemOrder);
    keywords.insert(QString("outer"), itemOuter);
    keywords.insert(QString("over"), itemOver);
    keywords.insert(QString("percent"), itemPercent);
    keywords.insert(QString("pivot"), itemPivot);
    keywords.insert(QString("plan"), itemPlan);
    keywords.insert(QString("precision"), itemPrecision);
    keywords.insert(QString("primary"), itemPrimary);
    keywords.insert(QString("print"), itemPrint);
    keywords.insert(QString("proc"), itemProc);
    keywords.insert(QString("procedure"), itemProcedure);
    keywords.insert(QString("public"), itemPublic);
    keywords.insert(QString("raisError"), itemRaisError);
    keywords.insert(QString("read"), itemRead);
    keywords.insert(QString("readText"), itemReadText);
    keywords.insert(QString("reconfigure"), itemReconfigure);
    keywords.insert(QString("references"), itemReferences);
    keywords.insert(QString("replication"), itemReplication);
    keywords.insert(QString("restore"), itemRestore);
    keywords.insert(QString("restrict"), itemRestrict);
    keywords.insert(QString("return"), itemReturn);
    keywords.insert(QString("revert"), itemRevert);
    keywords.insert(QString("revoke"), itemRevoke);
    keywords.insert(QString("right"), itemRight);
    keywords.insert(QString("rollback"), itemRollback);
    keywords.insert(QString("rowcount"), itemRowCount);
    keywords.insert(QString("rowguidcol"), itemRowGuidCol);
    keywords.insert(QString("rule"), itemRule);
    keywords.insert(QString("save"), itemSave);
    keywords.insert(QString("schema"), itemSchema);
    keywords.insert(QString("securityAudit"), itemSecurityAudit);
    keywords.insert(QString("select"), itemSelect);
    keywords.insert(QString("semantickeyphrasetable"), itemSemanticKeyPhraseTable);
    keywords.insert(QString("semanticsimilaritydetailstable"), itemSemanticSimilarityDetailsTable);
    keywords.insert(QString("semanticsimilaritytable"), itemSemanticSimilarityTable);
    keywords.insert(QString("session_user"), itemSession_user);
    keywords.insert(QString("set"), itemSet);
    keywords.insert(QString("setUser"), itemSetUser);
    keywords.insert(QString("shutdown"), itemShutdown);
    keywords.insert(QString("some"), itemSome);
    keywords.insert(QString("statistics"), itemStatistics);
    keywords.insert(QString("system_user"), itemSystem_user);
    keywords.insert(QString("table"), itemTable);
    keywords.insert(QString("tablesample"), itemTableSample);
    keywords.insert(QString("textsize"), itemTextSize);
    keywords.insert(QString("then"), itemThen);
    keywords.insert(QString("to"), itemTo);
    keywords.insert(QString("top"), itemTop);
    keywords.insert(QString("tran"), itemTran);
    keywords.insert(QString("transaction"), itemTransaction);
    keywords.insert(QString("trigger"), itemTrigger);
    keywords.insert(QString("truncate"), itemTruncate);
    keywords.insert(QString("try_convert"), itemTry_convert);
    keywords.insert(QString("tsequal"), itemTsequal);
    keywords.insert(QString("union"), itemUnion);
    keywords.insert(QString("unique"), itemUnique);
    keywords.insert(QString("unpivot"), itemUnpivot);
    keywords.insert(QString("update"), itemUpdate);
    keywords.insert(QString("updateText"), itemUpdateText);
    keywords.insert(QString("use"), itemUse);
    keywords.insert(QString("user"), itemUser);
    keywords.insert(QString("values"), itemValues);
    keywords.insert(QString("varying"), itemVarying);
    keywords.insert(QString("view"), itemView);
    keywords.insert(QString("waitfor"), itemWaitfor);
    keywords.insert(QString("when"), itemWhen);
    keywords.insert(QString("where"), itemWhere);
    keywords.insert(QString("while"), itemWhile);
    keywords.insert(QString("with"), itemWith);
    keywords.insert(QString("within"), itemWithin);
    keywords.insert(QString("writetext"), itemWriteText);
}

void lexer::emitt(itemType t) {
    items.append(item{t, lexem(), start, pos, lineNumber()});
    start = pos;
}

QString lexer::lexem() {
    return input.mid(start, pos - start);
}

// next returns the next rune in the input.
QChar lexer::next() {
    if (pos >= input.length()) {
        width = 0;
        return eof;
    }

    QChar rune = input.at(pos);
    width = 1;
    pos += width;
    return rune;
}

// ignore skips over the pending input before this point.
void lexer::ignore() {
    start = pos;
}

// backup steps back one rune.
// Can be called only once per call of next.
void lexer::backup() {
    pos -= width;
}

// peek returns but does not consume the next rune in the input.
QChar lexer::peek() {
    QChar r = next();
    backup();
    return r;
}

int lexer::lineNumber()
{
    QString scanned = input.mid(0, pos);
    return scanned.count("\n") + 1;
}

QSharedPointer<State> lexer::error(QString s, QChar r){
    qDebug() << s.arg(r);
    return QSharedPointer<State>();
}

QSharedPointer<State> lexer::error(QString s){
    qDebug() << s;
    return QSharedPointer<State>();
}

// accept consumes the next rune
// if it's from the valid set.
bool lexer::accept(QString valid) {
    if (valid.indexOf(next()) >= 0) {
        return true;
    }
    backup();
    return false;
}

// acceptRun consumes a run of runes from the valid set.
void lexer::acceptRun(QString valid) {
    while (valid.indexOf(next()) >= 0) {  }
    backup();
}

// run lexes the input by executing state functions until
// the state is nil.
void lexer::run() {
    QSharedPointer<State> state =
            QSharedPointer<LexStatement>(new LexStatement());
    while (!state.isNull()) {
        state = state->Execute(this);
    }
}
