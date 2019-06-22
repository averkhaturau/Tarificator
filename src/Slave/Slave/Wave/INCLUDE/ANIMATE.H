// animate.h : header file
//
// @doc
// All classes for animation
//

#ifndef __ANIMATE__
#define __ANIMATE__

#include <mmsystem.h>


class CWave;
class CWaveNotifyObj;

class CWaveInDevice : public CWnd
{

// Attributes
public:
    BOOL IsOpen(); 
    BOOL CanDoFormat(WAVEFORMAT* pFormat);

// Operations
public:
    CWaveInDevice();
    BOOL Open(int iID, WAVEFORMAT* pFormat);
    BOOL Open(int iID, PCMWAVEFORMAT* pFormat)
        {return Open(iID, (WAVEFORMAT*)pFormat);}
    BOOL Close();
    void WaveInData(CWave* pWave, WAVEHDR* pHdr);
    void Reset();
    BOOL Record(CWave* pWave,
                int iBlockSize = 4096);


// Implementation
public:
    virtual ~CWaveInDevice();

private:
    BOOL Create();

    HWAVEIN m_hInDev;               // input device handle
    int m_iBlockSize;
    int m_iBlockCount;              // number of blocks in the queue

    // Generated message map functions
protected:
    //{{AFX_MSG(CWaveInDev)
    afx_msg LRESULT OnWimData(WPARAM w, LPARAM l);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// @class CWaveOutDevice | This class encapsulates a waveform
//  output device driver.
// @base public | CWnd
// @member IsOpen | Test if the device is open.
// @member CanDoFormat | Test if the device supports a given format.
// @member Open | Open the device.
// @member Close | Close the device.
// @member Play | Start playing.
// @member Reset | Stop all actions and free buffers.

class CWaveOutDevice : public CWnd
{

// Attributes
public:
    BOOL IsOpen(); 
    BOOL CanDoFormat(WAVEFORMAT* pFormat);

// Operations
public:
    CWaveOutDevice();
    BOOL Open(WAVEFORMAT* pFormat);
    BOOL Open(PCMWAVEFORMAT* pFormat)
        {return Open((WAVEFORMAT*)pFormat);}
    BOOL Close();
    BOOL Play(CWave* pWave);
    void WaveOutDone(CWave* pWave, WAVEHDR* pHdr);
    void Reset();

// Implementation
public:
    virtual ~CWaveOutDevice();

private:
    BOOL Create();

    HWAVEOUT m_hOutDev;             // output device handle
    int m_iBlockCount;              // number of blocks in the queue

    // Generated message map functions
protected:
    //{{AFX_MSG(CWaveOutDev)
    afx_msg LRESULT OnWomDone(WPARAM w, LPARAM l);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

// some global items
extern CWaveOutDevice theDefaultWaveOutDevice;

/////////////////////////////////////////////////////////////////////////////
// @class CWaveBlock | This class encapsulates a block of
//  wave data.
// @base public | CObject
// @member CWaveBlock | Constructor.
// @member GetSamples | Get a pointer to the samples in the block.
// @member GetSize | Get the block size in bytes.
// @member GetNumSamples | Get the number of samples in the block.
// @member SetNumSamples | Set the number of samples in the block.

/*
@mfunc void* | CWaveBlock | GetSamples | Get a pointer to the sample data.
@syntax void* GetSamples();
@rdesc The return value is a pointer to the samples or NULL if no data
exists in the block.
@xref <c CWaveBlock>

@mfunc int | CWaveBlock | GetSize | Get the block size.
@syntax int GetSize();
@rdesc The return value is the size of the data block in bytes.
@xref <c CWaveBlock>

@mfunc int | CWaveBlock | GetNumSamples | Get the number of samples
in the block.
@syntax int GetNumSamples();
@rdesc The return value is the number of samples in the data block.
@xref <c CWaveBlock>

@mfunc void | CWaveBlock | SetNumSamples | Set the number of samples
in the block.
@syntax void SetNumSamples(int iCount);
@parm int | iCount | The new sample count.
@rdesc There is no return value.
@xref <c CWaveBlock>
*/

class CWaveBlock : public CObject
{
    DECLARE_SERIAL(CWaveBlock)
public:
    CWaveBlock();
    CWaveBlock(int iSize);
    CWaveBlock(void* pData, int iSize, int iSamples);     
    ~CWaveBlock();
    virtual void Serialize(CArchive& ar);
    void* GetSamples()
        {return m_pSamples;}
    int GetSample(int iSample, int iSampleSize);
    int GetSize()
        {return m_iSize;}
    int GetNumSamples()
        {return m_iNumSamples;}
    void SetNumSamples(int iCount)
        {m_iNumSamples = iCount;}   

public:
    void* m_pSamples;           // ptr to samples
    int m_iSize;                // size of block in bytes
    int m_iNumSamples;          // no of samples used in block
};

/////////////////////////////////////////////////////////////////////////////
// @class CWaveBlockList | This class provides a list of CWaveBlock objects.
// @base private | CObList
// @member FreeAll | Delete all blocks in the list.
// @member AppendBlock | Append a CWaveBlock to the list.
// @member IsEmpty | Test if the list is empty.
// @member GetCount | Get the number of blocks in the list.
// @member GetSample | Get a single sample from the block.
// @member RemoveHead | Remove the first block from the list.
// @member RemoveTail | Remove the last block from the list.

/*
@mfunc void | CWaveBlockList | AppendBlock | Add a new block to the end of
the list.
@syntax void AppendBlock(CWaveBlock* pBlock);
@parm CWaveBlock* | pBlock | A pointer to the new block to add to the list.
@rdesc There is no return value.
@xref <c CWaveBlocklist> <c CWaveBlock>
*/

class CWaveBlockList : private CObList
{
    DECLARE_SERIAL(CWaveBlockList)
public:
    CWaveBlockList();     
    ~CWaveBlockList();
    virtual void Serialize(CArchive& ar);
    void FreeAll();
    BOOL IsEmpty() 
        {return CObList::IsEmpty();}
    int GetCount()
        {return CObList::GetCount();}
    CWaveBlock* RemoveHead()
        {return (CWaveBlock*) CObList::RemoveHead();}
    CWaveBlock* RemoveTail()
        {return (CWaveBlock*) CObList::RemoveTail();}
    void AppendBlock(CWaveBlock* pBlock)
        {CObList::AddTail(pBlock);}
    POSITION GetHeadPosition() 
        {return CObList::GetHeadPosition();}
    CWaveBlock* GetNext(POSITION& rPos)
        {return (CWaveBlock*) CObList::GetNext(rPos);}                   
};


/////////////////////////////////////////////////////////////////////////////
// @class CWaveNotifyObj | This class provides a notification object
//  used by CWave objects.
// @base public | CObject
// @member NewData | Called when new data is added to a CWave object.
// @member EndPlayback | Called when playback of a CWave object stops.

/*
@mfunc int | CWaveNotifyObj | NewData | Called when new data arrives
in the owning CWave object.
@syntax virtual void NewData(CWave *pWave, CWaveBlock* pBlock) = 0;
@parm CWave | pWave | A pointer the the CWave object receiving the
new data.
@parm CWaveBlock | pBlock | A pointer to the CWaveBlock object receiving the
new data.
@rdesc There is no return value.
@comm This is a pure virtual function. You must derive your own class
from <c CWaveNotifyObj> and implement the <mf CWaveNotifyObj::NewData>
function in your derived class.
@xref <c CWaveNotifyObj> <c CWave> <c CWaveBlock>

@mfunc int | CWaveNotifyObj | EndPlayback | Called when playback of a
CWave object stops.
@syntax virtual void EndPlayback(CWave *pWave) = 0;
@parm CWave | pWave | A pointer the the CWave object which was
being played.
@rdesc There is no return value.
@comm This is a pure virtual function. You must derive your own class
from <c CWaveNotifyObj> and implement the <mf CWaveNotifyObj::Endplayback>
function in your derived class.
@xref <c CWaveNotifyObj> <c CWave> <c CWaveBlock>
*/

class CWaveNotifyObj : public CObject
{
public:
    virtual void NewData(CWave *pWave,
                         CWaveBlock* pBlock) = 0;
    virtual void EndPlayback(CWave *pWave) = 0;

		virtual ~CWaveNotifyObj() {};
};

/////////////////////////////////////////////////////////////////////////////
// @class CWave | This class encapsulates a waveform.
// @base public | CObject
// @member CWave | Constructor.
// @member AddRef | Increments the object's reference count.
// @member Release | Decrements the object's reference count and deletes
//  the object if the reference count falls to zero.
// @member Create | Create a new CWave object.
// @member Play | Start playing.
// @member Stop | Playing or recording.
// @member Load | Load a sound from a file.
// @member LoadResource | Load a sound from a resource.
// @member Record | Start recording.
// @member DeleteAll | Delete all samples.
// @member GetNumSamples | Get the number of samples in the waveform.
// @member GetFormat | Get the format of the waveform.
// @member GetOutDevice | Get the current output device.
// @member GetInDevice | Get the current input device.
// @member GetBlockList | Get the block list.
// @member GetSample | Get a single sample from the waveform.
// @member GetSampleRate | Get the sample rate.
// @member GetSampleSize | Get the size of each sample in bits.

/*
@mfunc WAVEFORMAT* | CWave | GetFormat | Get the format of the 
waveform.
@syntax WAVEFORMAT* GetFormat();
@rdesc The return value is a pointer to a WAVEFORMAT structure
which describes the format of the waveform.
@xref <c CWave>

@mfunc CWaveOutDevice* | CWave | GetOutDevice | Get the 
current output device.
@syntax CWaveOutDevice* GetOutDevice();
@rdesc The return value is a pointer to the current output
device or NULL if none is selected.
@xref <c CWave>

@mfunc CWaveInDevice* | CWave | GetInDevice | Get the 
current input device.
@syntax CWaveInDevice* GetInDevice();
@rdesc The return value is a pointer to the current input
device or NULL if none is selected.
@xref <c CWave>

@mfunc CWaveBlockList* | CWave | GetBlockList | Get a pointer
to the block list.
@syntax CWaveBlockList* GetBlockList();
@rdesc The return value is a pointer to a <c CWaveBlockList> object.
@xref <c CWave> <c CWaveBlockList>

@mfunc int | CWave | GetSampleRate | Get the sample rate.
@syntax int GetSampleRate();
@rdesc The return value is the sample rate in samples per second.
@comm Note that the sample rate is only applicable to certain types
of waveform.
@xref <c CWave>

@mfunc int | CWave | GetSampleSize | Get the sample size.
@syntax int GetSampleSize();
@rdesc The return value is the size of a sample in bits.
@xref <c CWave>

*/
class CWave : public CObject
{
public:
    enum WAVEFLAG {
        flagDefault         = 0x0000,
        flagAutoDestruct    = 0x0001
    };

    DECLARE_SERIAL(CWave)
public:
    CWave(WAVEFLAG flag = CWave::flagDefault);     
    virtual ~CWave();
    int AddRef();
    int Release();
    BOOL Create(int samprate = 11025,
                int sampsize = 8,
                int nSamples = 0);
    BOOL Create(PCMWAVEFORMAT* pFmt,
                int nSamples = 0);
    BOOL Play(CWaveOutDevice *pWaveOutDevice = NULL,
              CWaveNotifyObj* pNotify = NULL);
    void Stop();
    BOOL Load(const char *pszFileName = NULL);
    BOOL Load(CFile *fp);  
    BOOL Load(UINT hFile);
    BOOL Load(HMMIO hmmio);
    BOOL LoadResource(WORD wID);
    BOOL Record(CWaveInDevice* pDev,
                int iBlockSize = 4096,
                CWaveNotifyObj* pNotify = NULL);
    void DeleteAll();
    int GetNumSamples();
    int GetSample(int iSample);
    int GetSampleRate()
        {return m_pcmfmt.wf.nSamplesPerSec;}
    int GetSampleSize()
        {return m_pcmfmt.wBitsPerSample;}

// Attributes
public:
    WAVEFORMAT *GetFormat() 
        {return (WAVEFORMAT*)&m_pcmfmt;}
    CWaveOutDevice* GetOutDevice() 
        {return m_pOutDev;}
    CWaveInDevice* GetInDevice() 
        {return m_pInDev;}
    CWaveBlockList* GetBlockList()
        {return &m_BlockList;}
    void NewData(CWaveBlock* pBlock);


// Implementation
public:
    BOOL m_bAutoDestruct;       // die when not busy
    BOOL IsPlaying() 
        {return m_iPlayCount > 0 ? TRUE : FALSE;}
    void IncPlayCount() 
        {m_iPlayCount++;}
    void DecPlayCount(); 

protected:
    virtual void Serialize(CArchive& ar);   // overridden for document i/o

private:
    PCMWAVEFORMAT m_pcmfmt;     // pcm wave format header
    CWaveBlockList m_BlockList; // list of wave blocks
    CWaveOutDevice *m_pOutDev;  // output device
    CWaveInDevice *m_pInDev;    // input device
    int m_iRefCount;            // reference count
    int m_iPlayCount;           // no of blocks currently being played
    CWaveNotifyObj* m_pNotifyObj;
};


#endif // __ANIMATE__
