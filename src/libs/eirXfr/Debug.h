// file: {EIRC2 repo}./src/libs/eirType/Debug.h
#pragma once

#include <QtDebug>
#include <QCoreApplication>
#include <QDateTime>
#include <QPointer>
#include <QString>
#include <QTimer>

#define PTRSTRING(ptr) QString("%1=0x%2").arg(#ptr).arg(quintptr(ptr), sizeof(quintptr) / 4, 16, QChar('0'))
#define QOBJNAME(pqobj) ((nullptr == pqobj) ? ("{null} " #pqobj) : ("QObject:" #pqobj + pqobj->objectName()))
#define TIME QDateTime::currentDateTime().toString("hh:mm:ss.zzz")
#define DEBUG(qmt, pfx) qmt() << pfx << TIME << __LINE__
#define DEBUGQFI(qmt, pfx) qmt() << pfx << TIME << Q_FUNC_INFO << __LINE__
#define DEBUGQOB(qmt, pfx, mom) qmt() << pfx << TIME << Q_FUNC_INFO << __LINE__ << (mom ? mom->objectName() : "{orphan}");
#define DEBUGFN(qmt, pfx) { qmt() << pfx << TIME   << Q_FUNC_INFO << __LINE__; }
#define DEBUGPSZ(qmt, pfx, psz) { qmt(pfx << TIME  << __LINE__ psz); }
#define DEBUGQST(qmt, pfx, qst) { qmt(pfx << TIME << __LINE__  qPrintable(qst)); }
#define DEBUGDO(qmt, pfx, msg) { qmt() << pfx << TIME  << Q_FUNC_INFO << __LINE__ << "TODO:" << #msg; }
#define DEBUGUSE(qmt, pfx, var)  { (void)(var); qmt() << pfx << TIME   << Q_FUNC_INFO << __LINE__ << "TO USE:" << #var; }
#define DEBUGRTN(qmt, pfx, var)  {  return(var); qmt() << pfx << TIME   << Q_FUNC_INFO << __LINE__ << "TO RTN:" << #var; }
#define DEBUGEXP(qmt, pfx, bexpr) { if ( ! bexpr) qmt() << pfx << TIME  << Q_FUNC_INFO << __LINE__  << "Expectation FAILED:" << #bexpr; }
#define DEBUGEXPI(qmt, pfx, bexpr, info) { if ( ! bexpr) qmt() << pfx << TIME  << Q_FUNC_INFO << __LINE__  << "Expectation FAILED:" << #bexpr << info; }
#define DEBUGXN(qmt, pfx, bexpr) { if (bexpr) qmt() << pfx << TIME << Q_FUNC_INFO << __LINE__  << "Expectation FAILED:" << #bexpr; }
#define DEBUGXEQ(qmt, pfx, expt, var) { if (expt != var) qmt() << pfx << TIME << Q_FUNC_INFO << __LINE__ << "Expectation FAILED:" << #expt << expt << "==" << #var << var; }
#define DEBUGXNE(qmt, pfx, expt, var) { if (expt == var) qmt() << pfx << TIME << Q_FUNC_INFO << __LINE__ << "Expectation FAILED:" << #expt << expt << "!=" << #var << var; }
#define DEBUGXGT(qmt, pfx, expt, var) { if (expt <  var) qmt() << pfx << TIME << Q_FUNC_INFO << __LINE__ << "Expectation FAILED:" << #expt << expt << ">" << #var << var; }
#define DEBUGXPTR(qmt, pfx, ptr) if (nullptr == ptr) qmt() << pfx << TIME << Q_FUNC_INFO << __LINE__ << "Pointer FAILED:" <<  #ptr;
#define DEBUGPTR(qmt, pfx, ptr, expr)     if (ptr) ptr->expr else DEBUG(qmt, pfx) "Pointer" << #ptr << "FAILED for" << #expr;
#define DEBUGFNR(qmt, pfx, expr) { qmt() << pfx << TIME << Q_FUNC_INFO << __LINE__ << "Return:" << #expr << QString(expr); return expr; }
#define DEBUGRTV(qmt, pfx) { qmt() << pfx << TIME << Q_FUNC_INFO << __LINE__ << "Return(void)"; return; }
#define DEBUGQUIT Q_ASSERT(false);
#define DEBUGCON(qmt, pfx, src, sig, rec, slt) TSTALLOC(src); TSTALLOC(rec); if ( ! connect(src,sig,rec,slt)) DEBUG(qmt, pfx) << "Connect FAILED:" << #src << #sig << #rec << #slt;
#define DEBUGDCON(qmt, pfx, src, sig, rec, slt) TSTALLOC(src); TSTALLOC(rec); if ( ! disconnect(src,sig,rec,slt)) DEBUG(qmt, pfx) << "Disconnect FAILED:" << #src << #sig << #rec << #slt;

#define PINFO   "= INFO"
#define PDUMP   "~ DUMP"
#define PTRACE  "-TRACE"
#define PWARN   "* WARN"
#define PERROR  "#ERROR"
#define PABORT  "@FATAL"
#define PITODO  "=ITODO"
#define PTODO   "- TODO"
#define PWTODO  "*WTODO"
#define PETODO  "#ETODO"
#define PBTODO  "@FTODO"

#define INFO                    DEBUG(qInfo, PINFO) // << stuff
#define INFOQFI                 DEBUGQFI(qInfo, PINFO) // << stuff
#define INFOFN()                DEBUGFN(qInfo, PINFO);
#define INFOPSZ(psz)            DEBUGPSZ(qInfo, PINFO, psz);
#define INFOQST(qst)            DEBUGQST(qInfo, PINFO, qPrintable(qst));
#define NEXPECT(bexpr)          DEBUGEXP(qInfo, PINFO, bexpr)
#define NEXPECTEQ(expt, var)    DEBUGXEQ(qInfo, PINFO, expt, var)
#define NEXPECTNE(expt, var)    DEBUGXNE(qInfo, PINFO, expt, var)
#define LIKEDO(msg)             DEBUGDO(qInfo, PITODO, msg)

#define DUMP                    DEBUG(qDebug, PDUMP) // << stuff
#define DUMPVAL(val)            DUMP << #val << val;
#define TRACE                   DEBUG(qDebug, PTRACE) // << stuff
#define TRACEQFI                DEBUGQFI(qDebug, PTRACE) // << stuff
#define TRACEQOB(mom)           DEBUGQOB(qDebug, PTRACE, mom);
#define TRACEFN                 DEBUGFN(qDebug, PTRACE);
#define TRACEPSZ(psz)           DEBUGPSZ(qDebug, PTRACE, psz);
#define TRACEQST(qst)           DEBUGQST(qDebug, PTRACE, qPrintable(qst));
#define TEXPECT(bexpr)          DEBUGEXP(qDebug, PTRACE, bexpr)
#define TEXPECTEQ(expt, var)    DEBUGXEQ(qDebug, PTRACE, expt, var)
#define TEXPECTNE(expt, var)    DEBUGXNE(qDebug, PTRACE, expt, var)
#define TRACERTV()              DEBUGRTV(qDebug, PTRACE)
#define TRACERTN(expr)          TRACE << "return" << #expr << expr;
#define TRACEFNR(expr)          DEBUGFNR(qDebug, PTRACE, expr)
#define TODO(msg)               DEBUGDO(qDebug, PTODO, msg)
#define LATERDO(msg)            DEBUGDO(qDebug, PTODO, msg)
#define TOUSE(msg)              DEBUGUSE(qDebug, PTODO, msg)
#define TORTN(msg)              DEBUGRTN(qDebug, PTODO, msg)
#define UNUSED(var)             Q_UNUSED(var)
#define EMIT(expr)              DEBUG(qDebug, PTRACE) << "EMIT" << #expr; expr

#define WARN                    DEBUG(qWarning, PWARN) // << stuff
#define WARNQFI                 DEBUGQFI(qWarning, PWARN) // << stuff
#define WARNFN()                DEBUGFN(qWarning, PWARN);
#define WARNPSZ(psz)            DEBUGPSZ(qWarning, PWARN, psz);
#define WARNQST(qst)            DEBUGQST(qWarning, PWARN, qPrintable(qst));
#define WEXPECT(bexpr)          DEBUGEXP(qWarning, PWARN, bexpr)
#define WEXPECTI(bexpr, info)   DEBUGEXPI(qWarning, PWARN, bexpr, info)
#define WCONNECT(src, sig, dst, slt)    DEBUGCON(qWarning,  PWARN, src, sig, dst, slt)
#define WEXPECTNOT(bexpr)       DEBUGXN(qWarning, PWARN, bexpr)
#define WEXPECTEQ(expt, var)    DEBUGXEQ(qWarning, PWARN, expt, var)
#define WEXPECTNE(expt, var)    DEBUGXNE(qWarning, PWARN, expt, var)
#define WANTDO(msg)             DEBUGDO(qWarning, PWTODO, msg)
#define WANTUSE(msg)            DEBUGUSE(qWarning, PWTODO, msg)
#define WANTRTN(msg)            DEBUGRTN(qWarning, PWTODO, msg)
#define WPTR(ptr, expr)         DEBUGPTR(qWarning, PWARN, ptr, expr)

#define ERROR                   DEBUG(qCritical, PERROR) // << stuff
#define ERRORQFI                DEBUGQFI(qCritical, PERROR) // << stuff
#define ERRORFN()               DEBUGFN(qCritical, PERROR);
#define ERRORPSZ(psz)           DEBUGPSZ(qCritical, PERROR, psz);
#define ERRORQST(qst)           DEBUGQST(qCritical, PERROR, qPrintable(qst));
#define EXPECT(bexpr)           DEBUGEXP(qCritical, PERROR, bexpr)
#define EXPECT(bexpr)           DEBUGEXP(qCritical, PERROR, bexpr)
#define EXPECTNOT(bexpr)        DEBUGXN(qCritical, PERROR, bexpr)
#define EXPECTEQ(expt, var)     DEBUGXEQ(qCritical, PERROR, expt, var)
#define EXPECTNE(expt, var)     DEBUGXNE(qCritical, PERROR, expt, var)
#define EXPECTGT(expt, var)     DEBUGXGT(qCritical, PERROR, expt, var)
#define CONNECT(src, sig, dst, slt)    DEBUGCON(qCritical,  PERROR, src, sig, dst, slt)
#define DISCONNECT(src, sig, dst, slt) DEBUGDCON(qCritical, PERROR, src, sig, dst, slt)
#define NEEDDO(msg)             DEBUGDO(qCritical, PETODO, msg)
#define NEEDUSE(msg)            DEBUGUSE(qCritical, PETODO, msg)
#define NEEDRTN(msg)            DEBUGRTN(qCritical, PETODO, msg)
#define NEEDFNR(expr)           DEBUGFNR(qCritical, PETODO, expr)
#define NEEDRTV()               DEBUGRTV(qCritical, PETODO)
#define PTR(ptr, expr)          DEBUGPTR(qCritical, PERROR, ptr, expr)

#define ABORT(strm)             DEBUG(qCritical, PABORT) << strm; DEBUGQUIT
#define ABORTQFI(strm)          DEBUGQFI(qCritical, PABORT) << strm; DEBUGQUIT
#define ABORTFN()               DEBUGFN(qCritical, PABORT); DEBUGQUIT
#define ABORTPSZ(psz)           DEBUGPSZ(qCritical, PABORT, psz); DEBUGQUIT
#define ABORTQST(qst)           DEBUGQST(qCritical, PABORT, qPrintable(qst)); DEBUGQUIT
#define BEXPECT(bexpr)          DEBUGEXP(qCritical, PABORT, bexpr); if ( ! bexpr) DEBUGQUIT
#define BEXPECTNOT(bexpr)       DEBUGXN(qCritical, PABORT, bexpr); if (bexpr) DEBUGQUIT
#define BEXPECTEQ(expt, var)    DEBUGXEQ(qCritical, PABORT, expt, var); if (expt != var) DEBUGQUIT
#define BEXPECTNE(expt, var)    DEBUGXNE(qCritical, PABORT, expt, var); if (expt == var) DEBUGQUIT
#define BEXPECTPTR(ptr)         DEBUGXPTR(qCritical, PABORT, ptr); DEBUGQUIT
//#define BCONNECT(src, sig, dst, slt)    DEBUGCON(qCritical,  PERROR, src, sig, dst, slt); DEBUGQUIT
#define MUSTDO(msg)             DEBUGDO(qCritical, PBTODO, msg); DEBUGQUIT
#ifdef QT_DEBUG
#define RMUSTDO(msg)            DEBUGDO(qCritical, PETODO, msg)
#else
#define RMUSTDO(msg)            DEBUGDO(qCritical, PBTODO, msg); DEBUGQUIT
#endif
#define MUSTUSE(msg)            DEBUGUSE(qCritical, PBTODO, msg); DEBUGQUIT
#define MUSTRTN(msg)            DEBUGRTN(qCritical, PBTODO, msg); DEBUGQUIT
#define BPTR(ptr, expr)         DEBUGPTR(qCritical, PERROR, ptr, expr); DEBUGQUIT

#define TSTALLOC(ptr)           DEBUGXPTR(qCritical, PABORT, ptr);
#define TRYALLOC(typ, var, nexpr) typ * var = new nexpr; TSTALLOC(var)
//#define QOBJPTR(ptr)            ExeFlightRecorder::objectPointerString(#ptr, ptr)
